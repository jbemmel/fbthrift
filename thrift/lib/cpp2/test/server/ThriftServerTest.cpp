/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <chrono>
#include <memory>
#include <string>
#include <utility>

#include <boost/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <fmt/core.h>
#include <folly/portability/GMock.h>
#include <folly/portability/GTest.h>

#include <folly/Conv.h>
#include <folly/ExceptionWrapper.h>
#include <folly/Memory.h>
#include <folly/Optional.h>
#include <folly/Range.h>
#include <folly/SocketAddress.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/executors/MeteredExecutor.h>
#include <folly/experimental/coro/Sleep.h>
#include <folly/experimental/observer/SimpleObservable.h>
#include <folly/io/GlobalShutdownSocketSet.h>
#include <folly/io/async/AsyncServerSocket.h>
#include <folly/io/async/AsyncSocket.h>
#include <folly/io/async/AsyncSocketException.h>
#include <folly/io/async/AsyncTransport.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/test/TestSSLServer.h>
#include <folly/synchronization/test/Barrier.h>
#include <folly/system/ThreadName.h>
#include <wangle/acceptor/ServerSocketConfig.h>

#include <folly/io/async/AsyncSocket.h>
#include <proxygen/httpserver/HTTPServerOptions.h>
#include <thrift/lib/cpp/server/TServerEventHandler.h>
#include <thrift/lib/cpp/transport/THeader.h>
#include <thrift/lib/cpp2/GeneratedCodeHelper.h>
#include <thrift/lib/cpp2/PluggableFunction.h>
#include <thrift/lib/cpp2/async/HTTPClientChannel.h>
#include <thrift/lib/cpp2/async/HeaderClientChannel.h>
#include <thrift/lib/cpp2/async/PooledRequestChannel.h>
#include <thrift/lib/cpp2/async/RequestChannel.h>
#include <thrift/lib/cpp2/async/RocketClientChannel.h>
#include <thrift/lib/cpp2/security/extensions/ThriftParametersClientExtension.h>
#include <thrift/lib/cpp2/server/Cpp2Connection.h>
#include <thrift/lib/cpp2/server/Cpp2Worker.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <thrift/lib/cpp2/test/gen-cpp2/TestService.h>
#include <thrift/lib/cpp2/test/util/TestHeaderClientChannelFactory.h>
#include <thrift/lib/cpp2/test/util/TestInterface.h>
#include <thrift/lib/cpp2/test/util/TestThriftServerFactory.h>
#include <thrift/lib/cpp2/transport/http2/common/HTTP2RoutingHandler.h>
#include <thrift/lib/cpp2/util/ScopedServerInterfaceThread.h>
#include <thrift/lib/cpp2/util/ScopedServerThread.h>

#include <fizz/client/AsyncFizzClient.h>

#include <common/logging/logging.h>

using namespace apache::thrift;
using namespace apache::thrift::test;
using namespace apache::thrift::util;
using namespace apache::thrift::async;
using namespace apache::thrift::transport;
using namespace apache::thrift::concurrency;
using namespace std::literals;
using std::string;

DECLARE_int32(thrift_cpp2_protocol_reader_string_limit);

std::unique_ptr<HTTP2RoutingHandler> createHTTP2RoutingHandler(
    ThriftServer& server) {
  auto h2_options = std::make_unique<proxygen::HTTPServerOptions>();
  h2_options->threads = static_cast<size_t>(server.getNumIOWorkerThreads());
  h2_options->idleTimeout = server.getIdleTimeout();
  h2_options->shutdownOn = {SIGINT, SIGTERM};
  return std::make_unique<HTTP2RoutingHandler>(
      std::move(h2_options), server.getThriftProcessor(), server);
}

TEST(ThriftServer, H2ClientAddressTest) {
  class EchoClientAddrTestInterface : public TestServiceSvIf {
    void sendResponse(std::string& _return, int64_t /* size */) override {
      _return = getConnectionContext()->getPeerAddress()->describe();
    }
  };

  ScopedServerInterfaceThread runner(
      std::make_shared<EchoClientAddrTestInterface>());
  auto& thriftServer = dynamic_cast<ThriftServer&>(runner.getThriftServer());
  thriftServer.addRoutingHandler(createHTTP2RoutingHandler(thriftServer));

  folly::EventBase base;
  folly::AsyncSocket::UniquePtr socket(
      new folly::AsyncSocket(&base, runner.getAddress()));
  TestServiceAsyncClient client(
      HTTPClientChannel::newHTTP2Channel(std::move(socket)));
  auto channel =
      boost::polymorphic_downcast<HTTPClientChannel*>(client.getChannel());

  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_EQ(response, channel->getTransport()->getLocalAddress().describe());
}

TEST(ThriftServer, OnewayDeferredHandlerTest) {
  class OnewayTestInterface : public TestServiceSvIf {
   public:
    folly::Baton<> done;

    folly::Future<folly::Unit> future_noResponse(int64_t size) override {
      auto tm = getThreadManager();
      auto ctx = getConnectionContext();
      return folly::futures::sleep(std::chrono::milliseconds(size))
          .via(tm)
          .thenValue(
              [ctx](auto&&) { EXPECT_EQ("noResponse", ctx->getMethodName()); })
          .thenValue([this](auto&&) { done.post(); });
    }
  };

  auto handler = std::make_shared<OnewayTestInterface>();
  ScopedServerInterfaceThread runner(handler);

  handler->done.reset();
  auto client = runner.newClient<TestServiceAsyncClient>();
  client->sync_noResponse(100);
  ASSERT_TRUE(handler->done.try_wait_for(std::chrono::seconds(1)));
}

TEST(ThriftServer, ResponseTooBigTest) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  runner.getThriftServer().setMaxResponseSize(4096);
  auto client = runner.newClient<TestServiceAsyncClient>();

  std::string request(4096, 'a');
  std::string response;
  try {
    client->sync_echoRequest(response, request);
    ADD_FAILURE() << "should throw";
  } catch (const TApplicationException& tae) {
    EXPECT_EQ(
        tae.getType(),
        TApplicationException::TApplicationExceptionType::INTERNAL_ERROR);
  } catch (...) {
    ADD_FAILURE() << "unexpected exception thrown";
  }
}

class TestConnCallback : public folly::AsyncSocket::ConnectCallback {
 public:
  void connectSuccess() noexcept override {}

  void connectErr(const folly::AsyncSocketException& ex) noexcept override {
    exception.reset(new folly::AsyncSocketException(ex));
  }

  std::unique_ptr<folly::AsyncSocketException> exception;
};

TEST(ThriftServer, SSLClientOnPlaintextServerTest) {
  TestThriftServerFactory<TestInterface> factory;
  ScopedServerThread sst(factory.create());
  folly::EventBase base;
  auto sslCtx = std::make_shared<folly::SSLContext>();
  auto socket = TAsyncSSLSocket::newSocket(sslCtx, &base);
  TestConnCallback cb;
  socket->connect(&cb, *sst.getAddress());
  base.loop();
  ASSERT_TRUE(cb.exception);
  auto msg = cb.exception->what();
  EXPECT_NE(nullptr, strstr(msg, "unexpected message"));
}

TEST(ThriftServer, DefaultCompressionTest) {
  /* Tests the functionality of default transforms, ensuring the server properly
     applies them even if the client does not apply any transforms. */
  class Callback : public RequestCallback {
   public:
    explicit Callback(bool compressionExpected, uint16_t expectedTransform)
        : compressionExpected_(compressionExpected),
          expectedTransform_(expectedTransform) {}

   private:
    void requestSent() override {}

    void replyReceived(ClientReceiveState&& state) override {
      auto trans = state.header()->getTransforms();
      if (compressionExpected_) {
        EXPECT_EQ(trans.size(), 1);
        for (auto& tran : trans) {
          EXPECT_EQ(tran, expectedTransform_);
        }
      } else {
        EXPECT_EQ(trans.size(), 0);
      }
    }
    void requestError(ClientReceiveState&& state) override {
      state.exception().throw_exception();
    }
    bool compressionExpected_;
    uint16_t expectedTransform_;
  };

  TestThriftServerFactory<TestInterface> factory;
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());
  ScopedServerThread sst(server);
  folly::EventBase base;

  // no compression if client does not compress/send preference
  auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));
  client.sendResponse(std::make_unique<Callback>(false, 0), 64);
  base.loop();

  // Ensure that client transforms take precedence
  auto channel =
      boost::polymorphic_downcast<ClientChannel*>(client.getChannel());
  apache::thrift::CompressionConfig compressionConfig;
  compressionConfig.codecConfig_ref().ensure().set_zstdConfig();
  channel->setDesiredCompressionConfig(compressionConfig);
  client.sendResponse(
      std::make_unique<Callback>(
          true, apache::thrift::transport::THeader::ZSTD_TRANSFORM),
      64);
  base.loop();
}

TEST(ThriftServer, HeaderTest) {
  TestThriftServerFactory<TestInterface> factory;
  auto serv = factory.create();
  ScopedServerThread sst(serv);
  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());

  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  RpcOptions options;
  // Set it as a header directly so the client channel won't set a
  // timeout and the test won't throw TTransportException
  options.setWriteHeader(
      apache::thrift::transport::THeader::CLIENT_TIMEOUT_HEADER,
      folly::to<std::string>(10));
  try {
    client.sync_processHeader(options);
    ADD_FAILURE() << "should timeout";
  } catch (const TApplicationException& e) {
    EXPECT_EQ(
        e.getType(), TApplicationException::TApplicationExceptionType::TIMEOUT);
  }
}

TEST(ThriftServer, ServerEventHandlerTest) {
  class TestInterface : public TestServiceSvIf {
   public:
    void voidResponse() override {}
  };

  class TestEventHandler : public server::TServerEventHandler {
   public:
    void preServe(const folly::SocketAddress*) { ++preServeCalls; }
    void newConnection(TConnectionContext*) { ++newConnectionCalls; }
    void connectionDestroyed(TConnectionContext*) {
      ++connectionDestroyedCalls;
    }

    ssize_t preServeCalls{0};
    ssize_t newConnectionCalls{0};
    ssize_t connectionDestroyedCalls{0};
  };
  auto eh1 = std::make_shared<TestEventHandler>();
  auto eh2 = std::make_shared<TestEventHandler>();
  auto eh3 = std::make_shared<TestEventHandler>();
  auto eh4 = std::make_shared<TestEventHandler>();

  auto testIf = std::make_shared<TestInterface>();

  auto runner = std::make_unique<ScopedServerInterfaceThread>(
      testIf, "::1", 0, [&](auto& ts) {
        ts.setServerEventHandler(eh1);
        ts.addServerEventHandler(eh2);
        ts.addServerEventHandler(eh3);
        ts.setServerEventHandler(eh4);
      });

  EXPECT_EQ(0, eh1->preServeCalls);
  EXPECT_EQ(1, eh2->preServeCalls);
  EXPECT_EQ(1, eh3->preServeCalls);
  EXPECT_EQ(1, eh4->preServeCalls);

  auto client = runner->newClient<TestServiceAsyncClient>(
      nullptr, [](auto socket) mutable {
        return RocketClientChannel::newChannel(std::move(socket));
      });

  client->semifuture_voidResponse().get();

  EXPECT_EQ(0, eh1->newConnectionCalls);
  EXPECT_EQ(1, eh2->newConnectionCalls);
  EXPECT_EQ(1, eh3->newConnectionCalls);
  EXPECT_EQ(1, eh4->newConnectionCalls);

  runner.reset();

  EXPECT_EQ(0, eh1->connectionDestroyedCalls);
  EXPECT_EQ(1, eh2->connectionDestroyedCalls);
  EXPECT_EQ(1, eh3->connectionDestroyedCalls);
  EXPECT_EQ(1, eh4->connectionDestroyedCalls);
}

TEST(ThriftServer, GetPortTest) {
  ThriftServer server;
  EXPECT_EQ(server.getPort(), 0);

  folly::SocketAddress addr;
  addr.setFromLocalPort(8080);
  server.setAddress(addr);
  EXPECT_EQ(server.getPort(), 8080);

  server.setPort(8090);
  EXPECT_EQ(server.getPort(), 8090);

  server.setAddress(addr);
  EXPECT_EQ(server.getPort(), 8080);
}

namespace {
class ServerErrorCallback : public RequestCallback {
 private:
  struct PrivateCtor {};

 public:
  ServerErrorCallback(
      PrivateCtor,
      folly::fibers::Baton& baton,
      THeader& header,
      folly::exception_wrapper& ew)
      : baton_(baton), header_(header), ew_(ew) {}

  static std::unique_ptr<RequestCallback> create(
      folly::fibers::Baton& baton,
      THeader& header,
      folly::exception_wrapper& ew) {
    return std::make_unique<ServerErrorCallback>(
        PrivateCtor{}, baton, header, ew);
  }
  void requestSent() override {}
  void replyReceived(ClientReceiveState&& state) override {
    header_ = *state.extractHeader();
    ew_ = TestServiceAsyncClient::recv_wrapped_voidResponse(state);
    baton_.post();
  }
  void requestError(ClientReceiveState&&) override { ADD_FAILURE(); }

 private:
  folly::fibers::Baton& baton_;
  THeader& header_;
  folly::exception_wrapper& ew_;
};

void doLoadHeaderTest(bool isRocket) {
  static constexpr int kEmptyMetricLoad = 12345;

  auto makeClient = [=](auto& runner) {
    if (!isRocket) {
      return runner.template newClient<TestServiceAsyncClient>(
          folly::getGlobalCPUExecutor().get(), [](auto socket) mutable {
            return HeaderClientChannel::newChannel(std::move(socket));
          });
    } else {
      return runner.template newClient<TestServiceAsyncClient>(
          folly::getGlobalCPUExecutor().get(), RocketClientChannel::newChannel);
    }
  };

  auto checkLoadHeader = [](const auto& header,
                            folly::Optional<std::string> loadMetric) {
    auto& headers = header.getHeaders();
    auto load = [&]() -> folly::Optional<int64_t> {
      if (auto value = header.getServerLoad()) {
        return value;
      }
      if (auto* loadPtr = folly::get_ptr(headers, THeader::QUERY_LOAD_HEADER)) {
        return folly::to<int64_t>(*loadPtr);
      }
      return {};
    }();
    ASSERT_EQ(loadMetric.hasValue(), load.has_value());

    if (!loadMetric) {
      return;
    }

    folly::StringPiece loadSp(*loadMetric);
    if (loadSp.removePrefix("custom_load_metric_")) {
      EXPECT_EQ(loadSp, std::to_string(*load));
    } else if (loadSp.empty()) {
      EXPECT_EQ(kEmptyMetricLoad, *load);
    } else {
      FAIL() << "Unexpected load metric";
    }
  };

  class BlockInterface : public TestServiceSvIf {
   public:
    folly::Optional<folly::Baton<>> block;
    void voidResponse() override {
      if (block) {
        block.value().wait();
      }
    }
  };

  uint32_t nCalls = 0;
  ScopedServerInterfaceThread runner(
      std::make_shared<BlockInterface>(), "::1", 0, [&nCalls](auto& server) {
        server.setGetLoad([](const std::string& metric) {
          folly::StringPiece metricPiece(metric);
          if (metricPiece.removePrefix("custom_load_metric_")) {
            return folly::to<int32_t>(metricPiece.toString());
          } else if (metricPiece.empty()) {
            return kEmptyMetricLoad;
          }
          ADD_FAILURE() << "Unexpected load metric on request";
          return -42;
        });

        server.setIsOverloaded(
            [&nCalls](const auto*, const std::string* method) {
              EXPECT_EQ("voidResponse", *method);
              return ++nCalls == 4;
            });
      });

  auto client = makeClient(runner);

  {
    // No load header
    RpcOptions options;
    auto [_, header] = client->header_semifuture_voidResponse(options).get();
    checkLoadHeader(*header, folly::none);
  }

  {
    // Empty load header
    RpcOptions options;
    const std::string kLoadMetric;
    options.setWriteHeader(THeader::QUERY_LOAD_HEADER, kLoadMetric);
    auto [_, header] = client->header_semifuture_voidResponse(options).get();
    checkLoadHeader(*header, kLoadMetric);
  }

  {
    // Custom load header
    RpcOptions options;
    const std::string kLoadMetric{"custom_load_metric_789"};
    options.setWriteHeader(THeader::QUERY_LOAD_HEADER, kLoadMetric);
    auto [_, header] = client->header_semifuture_voidResponse(options).get();
    checkLoadHeader(*header, kLoadMetric);
  }

  {
    // Force server overload. Load should still be returned on server overload.
    RpcOptions options;
    const std::string kLoadMetric;
    options.setWriteHeader(THeader::QUERY_LOAD_HEADER, kLoadMetric);

    folly::fibers::Baton baton;
    THeader header;
    folly::exception_wrapper ew;
    auto callback = ServerErrorCallback::create(baton, header, ew);
    client->voidResponse(options, std::move(callback));
    baton.wait();

    // Check that request was actually rejected due to server overload
    const bool matched =
        ew.with_exception([](const TApplicationException& tae) {
          ASSERT_EQ(
              TApplicationException::TApplicationExceptionType::LOADSHEDDING,
              tae.getType());
        });
    ASSERT_TRUE(matched);
    checkLoadHeader(header, kLoadMetric);
  }

  {
    // Force queue timeout.
    // for Rocket: load should still be returned
    // for Header: load is not returned because of thread safety concerns.
    auto handler = dynamic_cast<BlockInterface*>(
        runner.getThriftServer().getProcessorFactory().get());
    handler->block.emplace();
    auto fut = client->semifuture_voidResponse();
    auto guard = folly::makeGuard([&] {
      handler->block.value().post();
      std::move(fut).get();
    });
    RpcOptions options;
    const std::string kLoadMetric;
    options.setWriteHeader(THeader::QUERY_LOAD_HEADER, kLoadMetric);
    options.setQueueTimeout(std::chrono::milliseconds(10));

    folly::fibers::Baton baton;
    THeader header;
    folly::exception_wrapper ew;
    auto callback = ServerErrorCallback::create(baton, header, ew);
    client->voidResponse(options, std::move(callback));
    baton.wait();

    // Check that request was actually rejected due to queue timeout
    const bool matched =
        ew.with_exception([](const TApplicationException& tae) {
          ASSERT_EQ(TApplicationException::TIMEOUT, tae.getType());
        });
    ASSERT_TRUE(matched);
    if (isRocket) {
      checkLoadHeader(header, kLoadMetric);
    } else {
      checkLoadHeader(header, folly::none);
    }

    EXPECT_EQ(
        *folly::get_ptr(header.getHeaders(), "ex"),
        kServerQueueTimeoutErrorCode);
  }

  {
    // Force task timeout.
    // for Rocket: load should still be returned
    // for Header: load is not returned because of thread safety concerns.
    auto handler = dynamic_cast<BlockInterface*>(
        runner.getThriftServer().getProcessorFactory().get());
    handler->block.emplace();

    RpcOptions options;
    const std::string kLoadMetric;
    options.setWriteHeader(THeader::QUERY_LOAD_HEADER, kLoadMetric);
    options.setTimeout(std::chrono::seconds(1));

    auto prevTaskExpireTime = runner.getThriftServer().getTaskExpireTime();
    auto prevUseClientTimeout = runner.getThriftServer().getUseClientTimeout();
    runner.getThriftServer().setTaskExpireTime(std::chrono::milliseconds(100));
    runner.getThriftServer().setUseClientTimeout(false);
    auto guard = folly::makeGuard([&] {
      handler->block.value().post();
      runner.getThriftServer().setTaskExpireTime(prevTaskExpireTime);
      runner.getThriftServer().setUseClientTimeout(prevUseClientTimeout);
    });

    folly::fibers::Baton baton;
    THeader header;
    folly::exception_wrapper ew;
    auto callback = ServerErrorCallback::create(baton, header, ew);
    client->voidResponse(options, std::move(callback));
    baton.wait();

    // Check that request was actually rejected due to task timeout
    const bool matched =
        ew.with_exception([](const TApplicationException& tae) {
          ASSERT_EQ(TApplicationException::TIMEOUT, tae.getType());
        });
    ASSERT_TRUE(matched);
    if (isRocket) {
      checkLoadHeader(header, kLoadMetric);
    } else {
      checkLoadHeader(header, folly::none);
    }

    EXPECT_EQ(
        *folly::get_ptr(header.getHeaders(), "ex"), kTaskExpiredErrorCode);
  }
}
} // namespace

TEST(ThriftServer, LoadHeaderTest_HeaderClientChannel) {
  doLoadHeaderTest(false);
}
TEST(ThriftServer, LoadHeaderTest_RocketClientChannel) {
  doLoadHeaderTest(true);
}

enum LatencyHeaderStatus {
  EXPECTED,
  NOT_EXPECTED,
};

static void validateLatencyHeaders(
    transport::THeader::StringToStringMap headers, LatencyHeaderStatus status) {
  bool isHeaderExpected = (status == LatencyHeaderStatus::EXPECTED);
  auto queueLatency = folly::get_optional(headers, kQueueLatencyHeader.str());
  ASSERT_EQ(isHeaderExpected, queueLatency.has_value());
  auto processLatency =
      folly::get_optional(headers, kProcessLatencyHeader.str());
  ASSERT_EQ(isHeaderExpected, processLatency.has_value());
  if (isHeaderExpected) {
    EXPECT_GE(folly::to<int64_t>(queueLatency.value()), 0);
    EXPECT_GE(folly::to<int64_t>(processLatency.value()), 0);
  }
}

TEST(ThriftServer, LatencyHeader_LoggingDisabled) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  folly::EventBase base;
  auto client = runner.newClient<TestServiceAsyncClient>(&base);

  RpcOptions rpcOptions;
  client->sync_voidResponse(rpcOptions);
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::NOT_EXPECTED);
}

//
// Test enforcement of egress memory limit -- setEgressMemoryLimit()
//
// Client issues a series of large requests but does not read their responses.
// The server should queue outgoing responses until the egress limit is reached,
// then drop the client connection along with all undelivered responses.
//
TEST(ThriftServer, EnforceEgressMemoryLimit) {
  class TestServiceHandler : public TestServiceSvIf {
   public:
    // only used to configure the server-side connection socket
    int echoInt(int) override {
      shrinkSocketWriteBuffer();
      return 0;
    }

    void echoRequest(
        std::string& _return, std::unique_ptr<std::string> req) override {
      _return = *std::move(req);
      barrier.wait();
    }

    folly::test::Barrier barrier{2};

   private:
    void shrinkSocketWriteBuffer() {
      auto const_transport =
          getRequestContext()->getConnectionContext()->getTransport();
      auto transport = const_cast<folly::AsyncTransport*>(const_transport);
      auto sock = transport->getUnderlyingTransport<folly::AsyncSocket>();
      sock->setSendBufSize(0); // (smallest possible size)
    }
  };

  // Allocate server
  auto handler = std::make_shared<TestServiceHandler>();
  auto runner = std::make_shared<ScopedServerInterfaceThread>(handler);
  auto& server = runner->getThriftServer();
  auto const kChunkSize = 1ul << 20; // (1 MiB)
  server.setEgressMemoryLimit(kChunkSize * 4); // (4 MiB)
  server.setWriteBatchingInterval(std::chrono::milliseconds::zero());

  // Allocate client
  folly::EventBase evb;
  auto clientSocket = folly::AsyncSocket::newSocket(&evb, runner->getAddress());
  auto clientSocketPtr = clientSocket.get();
  clientSocketPtr->setRecvBufSize(0); // set recv buffer as small as possible
  auto clientChannel = RocketClientChannel::newChannel(std::move(clientSocket));
  auto clientChannelPtr = clientChannel.get();
  TestServiceAsyncClient client(std::move(clientChannel));

  // Dummy request which triggers some server-side socket configuration
  client.sync_echoInt(42);

  // This is used to flush the client write queue
  apache::thrift::rocket::RocketClient::FlushList flushList;
  clientChannelPtr->setFlushList(&flushList);
  auto flushClientWrites = [&]() {
    auto cbs = std::move(flushList);
    while (!cbs.empty()) {
      auto* callback = &cbs.front();
      cbs.pop_front();
      callback->runLoopCallback();
    }
  };

  // Tests whether the client socket is still writable. We avoid reading from
  // the socket because we don't want to flush the server queue.
  auto isClientChannelGood = [&](std::chrono::seconds timeout) -> bool {
    const auto expires = std::chrono::steady_clock::now() + timeout;
    while (clientChannelPtr->good() &&
           std::chrono::steady_clock::now() < expires) {
      client.semifuture_noResponse(0); // (write-only)
      flushClientWrites();
      /* sleep override */ std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return clientChannelPtr->good();
  };

  std::vector<folly::SemiFuture<std::string>> fv;

  // Reach the egress buffer limit. Notice that the server will report a bit
  // less memory than expected because a small portion of the response data will
  // be buffered in the kernel.
  for (size_t b = 0; b < server.getEgressMemoryLimit(); b += kChunkSize) {
    std::string data(kChunkSize, 'a');
    fv.emplace_back(client.semifuture_echoRequest(std::move(data)));
    flushClientWrites();
    handler->barrier.wait();
  }

  // The client socket should still be open
  ASSERT_TRUE(isClientChannelGood(std::chrono::seconds(5)));

  // The next response should put us over the egress limit
  std::string data(kChunkSize, 'a');
  fv.emplace_back(client.semifuture_echoRequest(std::move(data)));
  flushClientWrites();
  handler->barrier.wait();

  // Wait for the connection to drop
  ASSERT_FALSE(isClientChannelGood(std::chrono::seconds(20)));

  // Start reading again
  clientChannelPtr->setFlushList(nullptr);
  clientSocketPtr->setRecvBufSize(65535);
  auto t = std::thread([&] { evb.loopForever(); });
  SCOPE_EXIT {
    evb.terminateLoopSoon();
    t.join();
  };

  // All responses should have exceptions.
  auto all = folly::collectAll(std::move(fv));
  all.wait();
  ASSERT_TRUE(all.hasValue());
  for (auto const& rsp : std::move(all).get()) {
    EXPECT_TRUE(rsp.hasException());
  }
}

TEST(ThriftServer, SocketWriteTimeout) {
  class TestServiceHandler : public TestServiceSvIf {
   public:
    void echoRequest(
        std::string& _return, std::unique_ptr<std::string>) override {
      _return = std::string(kResponseSize, 'x'); // big response
      barrier.wait();
    }

    folly::test::Barrier barrier{2};

   private:
    const size_t kResponseSize = 10ul << 20;
  };

  const std::chrono::seconds kSocketWriteTimeout{5};

  // Server
  auto handler = std::make_shared<TestServiceHandler>();
  auto runner = std::make_shared<ScopedServerInterfaceThread>(handler);
  auto& server = runner->getThriftServer();
  server.setSocketWriteTimeout(kSocketWriteTimeout);
  server.setWriteBatchingInterval(std::chrono::milliseconds::zero());

  // Client
  folly::EventBase evb;
  auto clientSocket = folly::AsyncSocket::newSocket(&evb, runner->getAddress());
  auto clientChannel = RocketClientChannel::newChannel(std::move(clientSocket));
  auto clientChannelPtr = clientChannel.get();
  TestServiceAsyncClient client(std::move(clientChannel));

  // Establish connection
  client.sync_noResponse(42);

  // This is used to flush the client write queue
  apache::thrift::rocket::RocketClient::FlushList flushList;
  clientChannelPtr->setFlushList(&flushList);
  auto flushClientWrites = [&]() {
    auto cbs = std::move(flushList);
    while (!cbs.empty()) {
      auto* callback = &cbs.front();
      cbs.pop_front();
      callback->runLoopCallback();
    }
  };

  // Issue a series of requests without reading responses. We need enough
  // data to fill both the write buffer on the server and the read buffer on the
  // client, so that the server will be forced to queue the responses.
  std::vector<folly::SemiFuture<std::string>> fv;
  for (auto i = 0; i < 10; i++) {
    fv.emplace_back(client.semifuture_echoRequest("ignored"));
    flushClientWrites();
    handler->barrier.wait();
  }

  // Trigger write timeout on the server
  /* sleep override */ std::this_thread::sleep_for(kSocketWriteTimeout * 2);

  // Start reading responses
  auto t = std::thread([&] { evb.loopForever(); });
  SCOPE_EXIT {
    evb.terminateLoopSoon();
    t.join();
  };

  // All responses should have failed
  auto all = folly::collectAll(std::move(fv));
  all.wait();
  ASSERT_TRUE(all.hasValue());
  for (auto const& rsp : std::move(all).get()) {
    EXPECT_TRUE(rsp.hasException());
  }
}

namespace long_shutdown {
namespace {

class BlockingTestInterface : public TestServiceSvIf {
 public:
  explicit BlockingTestInterface(folly::Baton<>& baton) : baton_(baton) {}

 private:
  void noResponse(int64_t) override {
    baton_.post();
    // Locks up the server and prevents clean shutdown
    /* sleep override */ std::this_thread::sleep_for(
        std::chrono::seconds::max());
  }

  folly::Baton<>& baton_;
};

// Delay on snapshot dumping thread to simulate work being done
std::chrono::milliseconds actualDumpSnapshotDelay = 0ms;
// The advertised max delay for the returned task
std::chrono::milliseconds requestedDumpSnapshotDelay = 0ms;

// Dummy exit code to signal that we did manage to finish the (fake) snapshot
constexpr int kExitCode = 156;

THRIFT_PLUGGABLE_FUNC_SET(
    apache::thrift::ThriftServer::DumpSnapshotOnLongShutdownResult,
    dumpSnapshotOnLongShutdown) {
  return {
      folly::futures::sleep(actualDumpSnapshotDelay).defer([](auto&&) {
        std::quick_exit(kExitCode);
      }),
      requestedDumpSnapshotDelay};
}

} // namespace
} // namespace long_shutdown

TEST(ThriftServerDeathTest, LongShutdown_DumpSnapshot) {
  EXPECT_EXIT(
      ({
        THRIFT_FLAG_SET_MOCK(dump_snapshot_on_long_shutdown, true);
        folly::Baton<> ready;
        ScopedServerInterfaceThread runner(
            std::make_shared<long_shutdown::BlockingTestInterface>(ready),
            [](ThriftServer& server) { server.setWorkersJoinTimeout(1s); });

        long_shutdown::requestedDumpSnapshotDelay = 1s;
        long_shutdown::actualDumpSnapshotDelay = 0ms;

        auto client = runner.newClient<TestServiceAsyncClient>();
        client->semifuture_noResponse(0).get();
        ready.wait();
      }),
      testing::ExitedWithCode(long_shutdown::kExitCode),
      "");
}

TEST(ThriftServerDeathTest, LongShutdown_DumpSnapshotTimeout) {
  EXPECT_DEATH(
      ({
        THRIFT_FLAG_SET_MOCK(dump_snapshot_on_long_shutdown, true);
        folly::Baton<> ready;
        ScopedServerInterfaceThread runner(
            std::make_shared<long_shutdown::BlockingTestInterface>(ready),
            [](ThriftServer& server) { server.setWorkersJoinTimeout(1s); });

        long_shutdown::requestedDumpSnapshotDelay = 500ms;
        long_shutdown::actualDumpSnapshotDelay = 60s;

        auto client = runner.newClient<TestServiceAsyncClient>();
        client->semifuture_noResponse(0).get();
        ready.wait();
      }),
      "Could not drain active requests within allotted deadline");
}

namespace {
enum class TransportType { Header, Rocket };
enum class Compression { Enabled, Disabled };
enum class ErrorType { Overload, AppOverload, MethodOverload, Client, Server };
} // namespace

class HeaderOrRocketTest : public testing::Test {
 public:
  TransportType transport = TransportType::Rocket;
  Compression compression = Compression::Enabled;

  auto makeClient(ScopedServerInterfaceThread& runner, folly::EventBase* evb) {
    return runner.newClient<TestServiceAsyncClient>(
        evb,
        [&](auto socket) mutable { return makeChannel(std::move(socket)); });
  }

  ClientChannel::Ptr makeChannel(folly::AsyncTransport::UniquePtr socket) {
    auto channel = [&]() -> ClientChannel::Ptr {
      if (transport == TransportType::Header) {
        return HeaderClientChannel::newChannel(std::move(socket));
      } else {
        return RocketClientChannel::newChannel(std::move(socket));
      }
    }();
    if (compression == Compression::Enabled) {
      apache::thrift::CompressionConfig compressionConfig;
      compressionConfig.codecConfig_ref().ensure().set_zstdConfig();
      channel->setDesiredCompressionConfig(compressionConfig);
    }
    return channel;
  }
};

class OverloadTest : public HeaderOrRocketTest,
                     public ::testing::WithParamInterface<
                         std::tuple<TransportType, Compression, ErrorType>> {
 public:
  ErrorType errorType;

  bool isCustomError() {
    return errorType == ErrorType::Client || errorType == ErrorType::Server;
  }

  LatencyHeaderStatus getLatencyHeaderStatus() {
    // we currently only report latency headers for Header,
    // and only when method handler was executed started running.
    return errorType == ErrorType::MethodOverload &&
            transport == TransportType::Header
        ? LatencyHeaderStatus::EXPECTED
        : LatencyHeaderStatus::NOT_EXPECTED;
  }

  void validateErrorHeaders(const RpcOptions& rpc) {
    auto& headers = rpc.getReadHeaders();
    if (errorType == ErrorType::Client) {
      EXPECT_EQ(*folly::get_ptr(headers, "ex"), kAppClientErrorCode);
      EXPECT_EQ(*folly::get_ptr(headers, "uex"), "name");
      EXPECT_EQ(*folly::get_ptr(headers, "uexw"), "message");
    } else if (errorType == ErrorType::Server) {
      EXPECT_EQ(*folly::get_ptr(headers, "uex"), "name");
      EXPECT_EQ(*folly::get_ptr(headers, "uexw"), "message");
    } else if (errorType == ErrorType::AppOverload) {
      EXPECT_EQ(*folly::get_ptr(headers, "ex"), kAppOverloadedErrorCode);
      EXPECT_EQ(folly::get_ptr(headers, "uex"), nullptr);
      EXPECT_EQ(folly::get_ptr(headers, "uexw"), nullptr);
    } else if (errorType == ErrorType::MethodOverload) {
      EXPECT_EQ(*folly::get_ptr(headers, "ex"), kAppOverloadedErrorCode);
      EXPECT_EQ(folly::get_ptr(headers, "uex"), nullptr);
      EXPECT_EQ(folly::get_ptr(headers, "uexw"), nullptr);
    } else if (errorType == ErrorType::Overload) {
      EXPECT_EQ(*folly::get_ptr(headers, "ex"), kOverloadedErrorCode);
      EXPECT_EQ(folly::get_ptr(headers, "uex"), nullptr);
      EXPECT_EQ(folly::get_ptr(headers, "uexw"), nullptr);
    } else {
      FAIL() << "Unknown error type: " << (int)errorType;
    }
  }

  void SetUp() override {
    std::tie(transport, compression, errorType) = GetParam();
  }
};

class HeaderOrRocket : public HeaderOrRocketTest,
                       public ::testing::WithParamInterface<TransportType> {
 public:
  void SetUp() override { transport = GetParam(); }
};

TEST_P(HeaderOrRocket, OnewayClientConnectionCloseTest) {
  static folly::Baton baton;

  class OnewayTestInterface : public TestServiceSvIf {
    void noResponse(int64_t) override { baton.post(); }
  };

  ScopedServerInterfaceThread runner(std::make_shared<OnewayTestInterface>());
  {
    auto client = makeClient(runner, nullptr);
    client->sync_noResponse(0);
  }
  bool posted = baton.try_wait_for(1s);
  EXPECT_TRUE(posted);
}

TEST_P(HeaderOrRocket, RequestParamsNullCheck) {
  class TestInterfaceSF : public TestServiceSvIf {
    folly::SemiFuture<folly::Unit> semifuture_voidResponse() override {
      EXPECT_NE(getRequestContext(), nullptr);
      EXPECT_NE(getThreadManager(), nullptr);
      EXPECT_NE(getEventBase(), nullptr);
      return folly::makeSemiFuture().deferValue([this](folly::Unit) {
        EXPECT_EQ(getRequestContext(), nullptr);
        EXPECT_EQ(getThreadManager(), nullptr);
        EXPECT_EQ(getEventBase(), nullptr);
      });
    }
  };

  class TestInterfaceCoro : public TestServiceSvIf {
    folly::coro::Task<void> co_voidResponse() override {
      EXPECT_NE(getRequestContext(), nullptr);
      EXPECT_NE(getThreadManager(), nullptr);
      EXPECT_NE(getEventBase(), nullptr);
      co_await folly::coro::co_reschedule_on_current_executor;
      EXPECT_EQ(getRequestContext(), nullptr);
      EXPECT_EQ(getThreadManager(), nullptr);
      EXPECT_EQ(getEventBase(), nullptr);
    }
  };
  {
    ScopedServerInterfaceThread runner(std::make_shared<TestInterfaceSF>());
    auto client = makeClient(runner, nullptr);
    client->semifuture_voidResponse().get();
  }
  {
    ScopedServerInterfaceThread runner(std::make_shared<TestInterfaceCoro>());
    auto client = makeClient(runner, nullptr);
    client->semifuture_voidResponse().get();
  }
}

TEST_P(HeaderOrRocket, OnewayQueueTimeTest) {
  static folly::Baton running, finished;
  static folly::Baton running2;

  class TestInterface : public TestServiceSvIf {
    void voidResponse() override {
      static int once;
      EXPECT_EQ(once++, 0);
      running.post();
      finished.wait();
    }
    void noResponse(int64_t) override { running2.post(); }
  };

  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  runner.getThriftServer().setQueueTimeout(100ms);

  auto client = makeClient(runner, nullptr);

  auto first = client->semifuture_voidResponse();
  EXPECT_TRUE(running.try_wait_for(1s));
  auto second = client->semifuture_noResponse(0);
  EXPECT_THROW(
      client->sync_voidResponse(RpcOptions{}.setTimeout(1s)),
      TApplicationException);
  finished.post();
  // even though 3rd request was loaded shedded, the second is oneway
  // and should have went through
  EXPECT_TRUE(running2.try_wait_for(1s));
}

TEST_P(HeaderOrRocket, Priority) {
  int callCount{0};
  class TestInterface : public TestServiceSvIf {
    int& callCount_;

   public:
    explicit TestInterface(int& callCount) : callCount_(callCount) {}
    void priorityHigh() override {
      callCount_++;
      EXPECT_EQ(
          getConnectionContext()->getRequestExecutionScope().getPriority(),
          PRIORITY::HIGH);
    }
    void priorityBestEffort() override {
      callCount_++;
      EXPECT_EQ(
          getConnectionContext()->getRequestExecutionScope().getPriority(),
          PRIORITY::BEST_EFFORT);
    }
  };

  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(callCount));
  folly::EventBase base;
  auto client = makeClient(runner, &base);
  client->sync_priorityHigh();
  client->sync_priorityBestEffort();
  EXPECT_EQ(callCount, 2);
}

namespace {
template <typename F, typename Duration = decltype(1s)>
bool blockWhile(F&& f, Duration duration = 1s) {
  auto now = std::chrono::steady_clock::now();
  while (f()) {
    if (std::chrono::steady_clock::now() > now + duration) {
      return false;
    }
    std::this_thread::yield();
  }
  return true;
}
} // namespace

TEST_P(HeaderOrRocket, ThreadManagerAdapterOverSimpleTMUpstreamPriorities) {
  class TestInterface : public TestServiceSvIf {
   public:
    TestInterface() {}
    void voidResponse() override { callback_(getThreadManager()); }
    folly::Function<void(folly::Executor*)> callback_;
  };

  auto handler = std::make_shared<TestInterface>();
  ScopedServerInterfaceThread runner(handler, "::1", 0, [&](auto& ts) {
    // empty executor will default to SimpleThreadManager
    auto executor = ThreadManager::newSimpleThreadManager("tm", 1);
    auto tm = std::make_shared<ThreadManagerExecutorAdapter>(executor);
    auto tf =
        std::make_shared<PosixThreadFactory>(PosixThreadFactory::ATTACHED);
    tm->threadFactory(tf);
    tm->start();
    ts.setThreadManager(tm);
  });
  std::make_shared<TestInterface>();
  auto client = makeClient(runner, nullptr);

  folly::Baton baton1;
  folly::Baton baton2;
  // First request blocks the CPU thread, then waits for more requests to be
  // scheduled from upstream, then schedules internal task on the same thread.
  // This internal task should execute before upstream tasks.
  int testCounter = 0;
  handler->callback_ = [&](auto executor) {
    baton1.post();
    baton2.wait();
    EXPECT_EQ(0, testCounter++);
    executor->add([&] { EXPECT_EQ(1, testCounter++); });
  };
  client->semifuture_voidResponse();
  baton1.wait();

  handler->callback_ = [&](auto) { EXPECT_EQ(2, testCounter++); };
  auto tm = runner.getThriftServer().getThreadManager();
  auto normalPriExecutor = dynamic_cast<ThreadManager*>(
      tm->getKeepAlive(NORMAL, ThreadManager::Source::INTERNAL).get());
  auto req2 = client->semifuture_voidResponse();
  EXPECT_TRUE(blockWhile(
      [&] { return normalPriExecutor->pendingUpstreamTaskCount() != 1; }));
  baton2.post();

  req2.wait();
  EXPECT_EQ(3, testCounter);
}

TEST_P(
    HeaderOrRocket, ThreadManagerAdapterOverMeteredExecutorUpstreamPriorities) {
  class TestInterface : public TestServiceSvIf {
   public:
    explicit TestInterface(int& testCounter) : testCounter_(testCounter) {}
    void voidResponse() override { callback_(getThreadManager()); }
    int echoInt(int value) override {
      EXPECT_EQ(value, testCounter_++);
      return value;
    }
    folly::Function<void(folly::Executor*)> callback_;
    int& testCounter_;
  };

  int testCounter = 0;
  auto handler = std::make_shared<TestInterface>(testCounter);
  ScopedServerInterfaceThread runner(handler, "::1", 0, [&](auto& ts) {
    auto executor = std::make_shared<folly::CPUThreadPoolExecutor>(
        1, std::make_shared<folly::NamedThreadFactory>("cpu"));
    auto tm = std::make_shared<ThreadManagerExecutorAdapter>(executor);
    tm->setNamePrefix("cpu");
    tm->threadFactory(
        std::make_shared<PosixThreadFactory>(PosixThreadFactory::ATTACHED));
    tm->start();
    ts.setThreadManager(tm);
  });
  auto client = makeClient(runner, nullptr);

  folly::Baton baton1;
  folly::Baton baton2;
  // First request blocks the CPU thread, then waits for more requests to be
  // scheduled from upstream, then schedules internal tasks on the same thread.
  // These internal tasks should execute before upstream tasks, except for the
  // first upstream task (because this is how metered scheduling works).
  handler->callback_ = [&](auto executor) {
    baton1.post();
    baton2.wait();
    EXPECT_EQ(0, testCounter++);
    executor->add([&] { EXPECT_EQ(2, testCounter++); });
    executor->add([&] { EXPECT_EQ(3, testCounter++); });
    executor->add([&] { EXPECT_EQ(4, testCounter++); });
  };
  client->semifuture_voidResponse();
  baton1.wait();

  // While first request is blocking the CPU thread, send more requests to
  // the server, and make sure they are added to the upstream queue.
  std::vector<folly::SemiFuture<int>> requests;
  auto sendRequestAndWait = [&](int expectedValue) {
    auto tm = runner.getThriftServer().getThreadManager();
    auto upstreamQueue = dynamic_cast<folly::MeteredExecutor*>(
        tm->getKeepAlive(NORMAL, ThreadManager::Source::UPSTREAM).get());
    auto numPendingReqs = upstreamQueue->pendingTasks();
    requests.emplace_back(client->semifuture_echoInt(expectedValue));
    numPendingReqs++;
    EXPECT_TRUE(blockWhile(
        [&] { return upstreamQueue->pendingTasks() != numPendingReqs; }));
  };
  sendRequestAndWait(1);
  sendRequestAndWait(5);
  sendRequestAndWait(6);
  sendRequestAndWait(7);

  baton2.post();
  for (auto& req : requests) {
    req.wait();
  }
  EXPECT_EQ(8, testCounter);
}

TEST_P(HeaderOrRocket, ThreadManagerAdapterManyPools) {
  int callCount{0};
  class TestInterface : public TestServiceSvIf {
    int& callCount_;

   public:
    explicit TestInterface(int& callCount) : callCount_(callCount) {}
    void priorityHigh() override {
      callCount_++;
      EXPECT_THAT(*folly::getCurrentThreadName(), testing::StartsWith("tm-1-"));
    }
    void priorityBestEffort() override {
      callCount_++;
      EXPECT_THAT(*folly::getCurrentThreadName(), testing::StartsWith("tm-4-"));
    }
    void voidResponse() override {
      callCount_++;
      EXPECT_EQ("cpu0", *folly::getCurrentThreadName());
    }
  };

  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(callCount), "::1", 0, [](auto& ts) {
        auto tm = std::shared_ptr<ThreadManagerExecutorAdapter>(
            new ThreadManagerExecutorAdapter(
                {nullptr,
                 nullptr,
                 nullptr,
                 std::make_shared<folly::CPUThreadPoolExecutor>(
                     1, std::make_shared<folly::NamedThreadFactory>("cpu")),
                 nullptr}));
        tm->setNamePrefix("tm");
        tm->threadFactory(
            std::make_shared<PosixThreadFactory>(PosixThreadFactory::ATTACHED));
        tm->start();
        ts.setThreadManager(tm);
      });
  folly::EventBase base;
  auto client = makeClient(runner, &base);
  client->sync_priorityHigh();
  client->sync_priorityBestEffort();
  client->sync_voidResponse();
  EXPECT_EQ(callCount, 3);
}

TEST_P(HeaderOrRocket, ThreadManagerAdapterSinglePool) {
  int callCount{0};
  class TestInterface : public TestServiceSvIf {
    int& callCount_;

   public:
    explicit TestInterface(int& callCount) : callCount_(callCount) {}
    void priorityHigh() override {
      callCount_++;
      EXPECT_EQ("cpu0", *folly::getCurrentThreadName());
    }
    void priorityBestEffort() override {
      callCount_++;
      EXPECT_EQ("cpu0", *folly::getCurrentThreadName());
    }
    void voidResponse() override {
      callCount_++;
      EXPECT_EQ("cpu0", *folly::getCurrentThreadName());
    }
  };

  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(callCount), "::1", 0, [](auto& ts) {
        auto tm = std::shared_ptr<ThreadManagerExecutorAdapter>(
            new ThreadManagerExecutorAdapter(
                std::make_shared<folly::CPUThreadPoolExecutor>(
                    1, std::make_shared<folly::NamedThreadFactory>("cpu"))));
        tm->setNamePrefix("tm");
        tm->threadFactory(
            std::make_shared<PosixThreadFactory>(PosixThreadFactory::ATTACHED));
        tm->start();
        ts.setThreadManager(tm);
      });
  folly::EventBase base;
  auto client = makeClient(runner, &base);
  client->sync_priorityHigh();
  client->sync_priorityBestEffort();
  client->sync_voidResponse();
  EXPECT_EQ(callCount, 3);
}

TEST_P(HeaderOrRocket, StickyToThreadPool) {
  int callCount{0};
  class TestInterface : public TestServiceSvIf {
    int& callCount_;

   public:
    explicit TestInterface(int& callCount) : callCount_(callCount) {}
    folly::SemiFuture<folly::Unit> semifuture_priorityHigh() override {
      EXPECT_THAT(
          *folly::getCurrentThreadName(), testing::StartsWith("foo-pri1"));
      return folly::makeSemiFuture().defer([=](auto&&) {
        callCount_++;
        EXPECT_THAT(
            *folly::getCurrentThreadName(), testing::StartsWith("foo-pri1"));
      });
    }
    folly::coro::Task<void> co_priorityBestEffort() override {
      callCount_++;
      EXPECT_THAT(
          *folly::getCurrentThreadName(), testing::StartsWith("foo-pri4"));
      co_await folly::coro::co_reschedule_on_current_executor;
      callCount_++;
      EXPECT_THAT(
          *folly::getCurrentThreadName(), testing::StartsWith("foo-pri4"));
      co_return;
    }
  };

  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(callCount), "::1", 0, [](auto& ts) {
        auto tm = PriorityThreadManager::newPriorityThreadManager(1);
        tm->setNamePrefix("foo");
        tm->start();
        ts.setThreadManager(tm);
      });
  folly::EventBase base;
  auto client = makeClient(runner, &base);
  client->sync_priorityHigh();
  client->sync_priorityBestEffort();
  EXPECT_EQ(callCount, 3);
}

TEST_P(HeaderOrRocket, CancellationTest) {
  class NotCalledBackHandler {
   public:
    explicit NotCalledBackHandler(
        std::unique_ptr<HandlerCallback<void>> callback)
        : thriftCallback_{std::move(callback)},
          cancelCallback_(
              thriftCallback_->getConnectionContext()
                  ->getConnectionContext()
                  ->getCancellationToken(),
              [this]() { requestCancelled(); }) {}

    folly::Baton<> cancelBaton;

   private:
    void requestCancelled() {
      // Invoke the thrift callback once the request has canceled.
      // Even after the request has been canceled handlers still should
      // eventually invoke the request callback.
      std::exchange(thriftCallback_, nullptr)
          ->exception(std::runtime_error("request cancelled"));
      cancelBaton.post();
    }

    std::unique_ptr<HandlerCallback<void>> thriftCallback_;
    folly::CancellationCallback cancelCallback_;
  };

  class NotCalledBackInterface : public TestServiceSvIf {
   public:
    using NotCalledBackHandlers =
        std::vector<std::shared_ptr<NotCalledBackHandler>>;

    void async_tm_notCalledBack(
        std::unique_ptr<HandlerCallback<void>> cb) override {
      auto handler = std::make_shared<NotCalledBackHandler>(std::move(cb));
      notCalledBackHandlers_.lock()->push_back(std::move(handler));
      handlersCV_.notify_one();
    }

    /**
     * Get all handlers for currently pending notCalledBack() thrift calls.
     *
     * If there is no call currently pending this function will wait for up to
     * the specified timeout for one to arrive.  If the timeout expires before a
     * notCalledBack() call is received an empty result set will be returned.
     */
    NotCalledBackHandlers getNotCalledBackHandlers(
        std::chrono::milliseconds timeout) {
      auto end_time = std::chrono::steady_clock::now() + timeout;

      NotCalledBackHandlers results;
      auto handlers = notCalledBackHandlers_.lock();
      if (!handlersCV_.wait_until(handlers.as_lock(), end_time, [&] {
            return !handlers->empty();
          })) {
        // If we get here we timed out.
        // Just return an empty result set in this case.
        return results;
      }
      results.swap(*handlers);
      return results;
    }

   private:
    folly::Synchronized<NotCalledBackHandlers, std::mutex>
        notCalledBackHandlers_;
    std::condition_variable handlersCV_;
  };
  ScopedServerInterfaceThread runner(
      std::make_shared<NotCalledBackInterface>());
  folly::EventBase base;
  auto client = makeClient(runner, &base);

  auto interface = std::dynamic_pointer_cast<NotCalledBackInterface>(
      runner.getThriftServer().getProcessorFactory());
  runner.getThriftServer().setTaskExpireTime(0s);
  ASSERT_TRUE(interface);
  EXPECT_EQ(0, interface->getNotCalledBackHandlers(0s).size());

  // Make a call to notCalledBack(), which will time out since the server never
  // reponds to this API.
  try {
    RpcOptions rpcOptions;
    rpcOptions.setTimeout(std::chrono::milliseconds(10));
    client->sync_notCalledBack(rpcOptions);
    EXPECT_FALSE(true) << "request should have never returned";
  } catch (const TTransportException& tte) {
    if (tte.getType() != TTransportException::TIMED_OUT) {
      throw;
    }
  }

  // Wait for the server to register the call
  auto handlers = interface->getNotCalledBackHandlers(10s);
  ASSERT_EQ(1, handlers.size()) << "expected a single notCalledBack() call";
  auto wasCancelled = handlers[0]->cancelBaton.ready();
  // Currently we do not trigger per-request cancellations, but only
  // when client closes the connection.
  EXPECT_FALSE(wasCancelled);

  // Close the client.  This should trigger request cancellation on the server.
  client.reset();

  // The handler's cancellation token should be triggered when we close the
  // connection.
  wasCancelled = handlers[0]->cancelBaton.try_wait_for(10s);
  EXPECT_TRUE(wasCancelled);
}

TEST_P(HeaderOrRocket, QueueTimeoutOnServerShutdown) {
  class BlockInterface : public TestServiceSvIf {
   public:
    folly::Baton<> started, resume;
    bool once{true};
    void voidResponse() override {
      if (once) {
        once = false;
        started.post();
        EXPECT_TRUE(resume.try_wait_for(2s));
        // Wait for the server to start shutdown
        auto worker = getRequestContext()->getConnectionContext()->getWorker();
        while (!worker->isStopping()) {
          std::this_thread::yield();
        }
      }
    }
  };

  auto blockIf = std::make_shared<BlockInterface>();
  auto runner = std::make_unique<ScopedServerInterfaceThread>(blockIf);
  auto client = makeClient(*runner.get(), folly::getEventBase());

  auto first = client->semifuture_voidResponse();
  // Wait for the first request to start processing
  blockIf->started.wait();

  // Send second request
  folly::fibers::Baton baton;
  THeader th;
  folly::exception_wrapper ew;
  client->voidResponse(ServerErrorCallback::create(baton, th, ew));

  // Wait for the second connection to reach the server
  while (runner->getThriftServer().getActiveRequests() < 2) {
    std::this_thread::yield();
  }
  blockIf->resume.post();
  // Initiate server shutdown
  runner.reset();
  std::move(first).get();

  baton.wait();
  ASSERT_TRUE(ew.with_exception([](const TApplicationException& tae) {
    EXPECT_EQ(TApplicationException::TIMEOUT, tae.getType());
  }));
  EXPECT_EQ(
      *folly::get_ptr(th.getHeaders(), "ex"), kServerQueueTimeoutErrorCode);
}

INSTANTIATE_TEST_CASE_P(
    HeaderOrRocket,
    HeaderOrRocket,
    testing::Values(TransportType::Header, TransportType::Rocket));

TEST_P(OverloadTest, Test) {
  class BlockInterface : public TestServiceSvIf {
   public:
    folly::Baton<> block;
    void voidResponse() override { block.wait(); }

    void async_eb_eventBaseAsync(
        std::unique_ptr<HandlerCallback<std::unique_ptr<::std::string>>>
            callback) override {
      callback->appOverloadedException("loadshedding request");
    }
  };

  ScopedServerInterfaceThread runner(std::make_shared<BlockInterface>());
  folly::EventBase base;
  auto client = makeClient(runner, &base);

  runner.getThriftServer().setIsOverloaded(
      [&](const auto*, const string* method) {
        if (errorType == ErrorType::AppOverload) {
          EXPECT_EQ("voidResponse", *method);
          return true;
        }
        return false;
      });

  runner.getThriftServer().setPreprocess([&](auto&) -> PreprocessResult {
    if (errorType == ErrorType::Client) {
      return {AppClientException("name", "message")};
    } else if (errorType == ErrorType::Server) {
      return {AppServerException("name", "message")};
    }
    return {};
  });

  // force overloaded
  folly::Function<void()> onExit = [] {};
  auto guard = folly::makeGuard([&] { onExit(); });
  if (errorType == ErrorType::Overload) {
    // Thrift is overloaded on max requests
    runner.getThriftServer().setMaxRequests(1);
    auto handler = dynamic_cast<BlockInterface*>(
        runner.getThriftServer().getProcessorFactory().get());
    client->semifuture_voidResponse();
    while (runner.getThriftServer().getActiveRequests() < 1) {
      std::this_thread::yield();
    }
    onExit = [handler] { handler->block.post(); };
  }

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  try {
    if (errorType == ErrorType::MethodOverload) {
      std::string dummy;
      client->sync_eventBaseAsync(rpcOptions, dummy);
    } else {
      client->sync_voidResponse(rpcOptions);
    }
    FAIL() << "Expected that the service call throws TApplicationException";
  } catch (const apache::thrift::TApplicationException& ex) {
    auto expectType = isCustomError() ? TApplicationException::UNKNOWN
                                      : TApplicationException::LOADSHEDDING;
    EXPECT_EQ(expectType, ex.getType());
    auto expectMessage = isCustomError() ? "message" : "loadshedding request";
    EXPECT_EQ(expectMessage, ex.getMessage());

    validateErrorHeaders(rpcOptions);

    // Latency headers are NOT set, when server is overloaded
    validateLatencyHeaders(
        rpcOptions.getReadHeaders(), getLatencyHeaderStatus());
  } catch (...) {
    FAIL()
        << "Expected that the service call throws TApplicationException, got "
        << folly::exceptionStr(std::current_exception());
  }
}

INSTANTIATE_TEST_CASE_P(
    OverloadTestsFixture,
    OverloadTest,
    ::testing::Combine(
        testing::Values(TransportType::Header, TransportType::Rocket),
        testing::Values(Compression::Enabled, Compression::Disabled),
        testing::Values(
            ErrorType::Overload,
            ErrorType::MethodOverload,
            ErrorType::AppOverload,
            ErrorType::Client,
            ErrorType::Server)));

TEST(ThriftServer, LatencyHeader_ClientTimeout) {
  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(), "::1", 0, [](auto& server) {
        server.setUseClientTimeout(false);
      });
  auto client =
      runner.newClient<TestServiceAsyncClient>(nullptr, [](auto socket) {
        return HeaderClientChannel::newChannel(std::move(socket));
      });

  RpcOptions rpcOptions;
  // Setup client timeout
  rpcOptions.setTimeout(std::chrono::milliseconds(1));
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  std::string response;
  EXPECT_ANY_THROW(client->sync_sendResponse(rpcOptions, response, 20000));

  // Latency headers are NOT set, when client times out.
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::NOT_EXPECTED);
}

TEST(ThriftServer, LatencyHeader_RequestSuccess) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  auto client =
      runner.newClient<TestServiceAsyncClient>(nullptr, [](auto socket) {
        return HeaderClientChannel::newChannel(std::move(socket));
      });

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  client->sync_voidResponse(rpcOptions);
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::EXPECTED);
}

TEST(ThriftServer, LatencyHeader_RequestFailed) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  auto client =
      runner.newClient<TestServiceAsyncClient>(nullptr, [](auto socket) {
        return HeaderClientChannel::newChannel(std::move(socket));
      });

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  EXPECT_ANY_THROW(client->sync_throwsHandlerException(rpcOptions));

  // Latency headers are set, when handler throws exception
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::EXPECTED);
}

TEST(ThriftServer, LatencyHeader_TaskExpiry) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  auto client =
      runner.newClient<TestServiceAsyncClient>(nullptr, [](auto socket) {
        return HeaderClientChannel::newChannel(std::move(socket));
      });

  // setup task expire timeout.
  runner.getThriftServer().setTaskExpireTime(std::chrono::milliseconds(10));
  runner.getThriftServer().setUseClientTimeout(false);

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  std::string response;
  EXPECT_ANY_THROW(client->sync_sendResponse(rpcOptions, response, 30000));

  // Latency headers are set, when task expires
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::EXPECTED);
}

TEST(ThriftServer, LatencyHeader_QueueTimeout) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  auto client =
      runner.newStickyClient<TestServiceAsyncClient>(nullptr, [](auto socket) {
        return HeaderClientChannel::newChannel(std::move(socket));
      });

  // setup timeout
  runner.getThriftServer().setQueueTimeout(std::chrono::milliseconds(5));

  // Run a long request.
  auto slowRequestFuture = client->semifuture_sendResponse(20000);

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader(kClientLoggingHeader.str(), "");
  std::string response;
  EXPECT_ANY_THROW(client->sync_sendResponse(rpcOptions, response, 1000));

  // Latency headers are set, when server throws queue timeout
  validateLatencyHeaders(
      rpcOptions.getReadHeaders(), LatencyHeaderStatus::EXPECTED);

  folly::EventBase base;
  std::move(slowRequestFuture).via(&base).getVia(&base);
}

TEST(ThriftServer, ClientTimeoutTest) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = factory.create();
  ScopedServerThread sst(server);
  folly::EventBase base;

  auto getClient = [&base, &sst]() {
    auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());

    return std::make_shared<TestServiceAsyncClient>(
        HeaderClientChannel::newChannel(std::move(socket)));
  };

  int cbCtor = 0;
  int cbCall = 0;

  auto callback = [&cbCall, &cbCtor](
                      std::shared_ptr<TestServiceAsyncClient> client,
                      bool& timeout) {
    cbCtor++;
    return std::unique_ptr<RequestCallback>(new FunctionReplyCallback(
        [&cbCall, client, &timeout](ClientReceiveState&& state) {
          cbCall++;
          if (state.exception()) {
            timeout = true;
            auto ex = state.exception().get_exception();
            auto& e = dynamic_cast<TTransportException const&>(*ex);
            EXPECT_EQ(TTransportException::TIMED_OUT, e.getType());
            return;
          }
          try {
            std::string resp;
            client->recv_sendResponse(resp, state);
          } catch (const TApplicationException& e) {
            timeout = true;
            EXPECT_EQ(TApplicationException::TIMEOUT, e.getType());
            EXPECT_TRUE(
                state.header()->getFlags() & HEADER_FLAG_SUPPORT_OUT_OF_ORDER);
            return;
          }
          timeout = false;
        }));
  };

  // Set the timeout to be 5 milliseconds, but the call will take 10 ms.
  // The server should send a timeout after 5 milliseconds
  RpcOptions options;
  options.setTimeout(std::chrono::milliseconds(5));
  auto client1 = getClient();
  bool timeout1;
  client1->sendResponse(options, callback(client1, timeout1), 10000);
  base.loop();
  EXPECT_TRUE(timeout1);
  usleep(10000);

  // This time we set the timeout to be 100 millseconds.  The server
  // should not time out
  options.setTimeout(std::chrono::milliseconds(100));
  client1->sendResponse(options, callback(client1, timeout1), 10000);
  base.loop();
  EXPECT_FALSE(timeout1);
  usleep(10000);

  // This time we set server timeout to be 5 millseconds.  However, the
  // task should start processing within that millisecond, so we should
  // not see an exception because the client timeout should be used after
  // processing is started
  server->setTaskExpireTime(std::chrono::milliseconds(5));
  client1->sendResponse(options, callback(client1, timeout1), 10000);
  base.loop();
  usleep(10000);

  // The server timeout stays at 5 ms, but we put the client timeout at
  // 5 ms.  We should timeout even though the server starts processing within
  // 5ms.
  options.setTimeout(std::chrono::milliseconds(5));
  client1->sendResponse(options, callback(client1, timeout1), 10000);
  base.loop();
  EXPECT_TRUE(timeout1);
  usleep(50000);

  // And finally, with the server timeout at 50 ms, we send 2 requests at
  // once.  Because the first request will take more than 50 ms to finish
  // processing (the server only has 1 worker thread), the second request
  // won't start processing until after 50ms, and will timeout, despite the
  // very high client timeout.
  // We don't know which one will timeout (race conditions) so we just check
  // the xor
  auto client2 = getClient();
  bool timeout2;
  server->setTaskExpireTime(std::chrono::milliseconds(50));
  options.setTimeout(std::chrono::milliseconds(110));
  client1->sendResponse(options, callback(client1, timeout1), 100000);
  client2->sendResponse(options, callback(client2, timeout2), 100000);
  base.loop();
  EXPECT_TRUE(timeout1 || timeout2);
  EXPECT_FALSE(timeout1 && timeout2);

  EXPECT_EQ(cbCall, cbCtor);
}

TEST(ThriftServer, ConnectionIdleTimeoutTest) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = factory.create();
  server->setIdleTimeout(std::chrono::milliseconds(20));
  apache::thrift::util::ScopedServerThread st(server);

  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *st.getAddress());

  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  std::string response;
  client.sync_sendResponse(response, 200);
  EXPECT_EQ(response, "test200");
  base.loop();
}

TEST(ThriftServer, BadSendTest) {
  class Callback : public RequestCallback {
    void requestSent() override { ADD_FAILURE(); }
    void replyReceived(ClientReceiveState&&) override { ADD_FAILURE(); }
    void requestError(ClientReceiveState&& state) override {
      EXPECT_TRUE(state.exception());
      auto ex =
          state.exception()
              .get_exception<apache::thrift::transport::TTransportException>();
      ASSERT_TRUE(ex);
      EXPECT_THAT(
          ex->what(), testing::StartsWith("transport is closed in write()"));
    }
  };

  TestThriftServerFactory<TestInterface> factory;
  ScopedServerThread sst(factory.create());
  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());
  auto socketPtr = socket.get();
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  client.sendResponse(std::unique_ptr<RequestCallback>(new Callback), 64);

  socketPtr->shutdownWriteNow();
  base.loop();

  std::string response;
  EXPECT_THROW(client.sync_sendResponse(response, 64), TTransportException);
}

TEST(ThriftServer, ResetStateTest) {
  folly::EventBase base;

  // Create a server socket and bind, don't listen.  This gets us a
  // port to test with which is guaranteed to fail.
  auto ssock = std::unique_ptr<
      folly::AsyncServerSocket,
      folly::DelayedDestruction::Destructor>(new folly::AsyncServerSocket);
  ssock->bind(0);
  EXPECT_FALSE(ssock->getAddresses().empty());

  // We do this loop a bunch of times, because the bug which caused
  // the assertion failure was a lost race, which doesn't happen
  // reliably.
  for (int i = 0; i < 1000; ++i) {
    auto socket =
        folly::AsyncSocket::newSocket(&base, ssock->getAddresses()[0]);

    // Create a client.
    TestServiceAsyncClient client(
        HeaderClientChannel::newChannel(std::move(socket)));

    std::string response;
    // This will fail, because there's no server.
    EXPECT_THROW(client.sync_sendResponse(response, 64), TTransportException);
    // On a failed client object, this should also throw an exception.
    // In the past, this would generate an assertion failure and
    // crash.
    EXPECT_THROW(client.sync_sendResponse(response, 64), TTransportException);
  }
}

TEST_P(HeaderOrRocket, FailureInjection) {
  enum ExpectedFailure { NONE = 0, ERROR, TIMEOUT, DISCONNECT, END };

  std::atomic<ExpectedFailure> expected(NONE);

  using apache::thrift::transport::TTransportException;

  class Callback : public RequestCallback {
   public:
    explicit Callback(const std::atomic<ExpectedFailure>* expected)
        : expected_(expected) {}

   private:
    void requestSent() override {}

    void replyReceived(ClientReceiveState&& state) override {
      std::string response;
      try {
        TestServiceAsyncClient::recv_sendResponse(response, state);
        EXPECT_EQ(NONE, *expected_);
      } catch (const apache::thrift::TApplicationException&) {
        const auto& headers = state.header()->getHeaders();
        EXPECT_TRUE(
            headers.find("ex") != headers.end() &&
            headers.find("ex")->second == kInjectedFailureErrorCode);
        EXPECT_EQ(ERROR, *expected_);
      } catch (...) {
        ADD_FAILURE() << "Unexpected exception thrown";
      }

      // Now do it again with exception_wrappers.
      auto ew =
          TestServiceAsyncClient::recv_wrapped_sendResponse(response, state);
      if (ew) {
        EXPECT_TRUE(
            ew.is_compatible_with<apache::thrift::TApplicationException>());
        EXPECT_EQ(ERROR, *expected_);
      } else {
        EXPECT_EQ(NONE, *expected_);
      }
    }

    void requestError(ClientReceiveState&& state) override {
      ASSERT_TRUE(state.exception());
      auto ex_ = state.exception().get_exception();
      auto& ex = dynamic_cast<TTransportException const&>(*ex_);
      if (ex.getType() == TTransportException::TIMED_OUT) {
        EXPECT_EQ(TIMEOUT, *expected_);
      } else {
        EXPECT_EQ(DISCONNECT, *expected_);
      }
    }

    const std::atomic<ExpectedFailure>* expected_;
  };

  ScopedServerInterfaceThread sst(std::make_shared<TestInterface>());
  folly::EventBase base;
  auto client = makeClient(sst, &base);

  auto& server = sst.getThriftServer();
  SCOPE_EXIT { server.setFailureInjection(ThriftServer::FailureInjection()); };

  RpcOptions rpcOptions;
  rpcOptions.setTimeout(std::chrono::milliseconds(100));
  for (int i = 0; i < END; ++i) {
    auto exp = static_cast<ExpectedFailure>(i);
    ThriftServer::FailureInjection fi;
    LOG(INFO) << i;
    switch (exp) {
      case NONE:
        break;
      case ERROR:
        fi.errorFraction = 1;
        break;
      case TIMEOUT:
        fi.dropFraction = 1;
        break;
      case DISCONNECT:
        fi.disconnectFraction = 1;
        break;
      case END:
        LOG(FATAL) << "unreached";
    }

    server.setFailureInjection(std::move(fi));

    expected = exp;

    auto callback = std::make_unique<Callback>(&expected);
    client->sendResponse(rpcOptions, std::move(callback), 1);
    base.loop();
  }
}

TEST(ThriftServer, useExistingSocketAndExit) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());
  folly::AsyncServerSocket::UniquePtr serverSocket(
      new folly::AsyncServerSocket);
  serverSocket->bind(0);
  server->useExistingSocket(std::move(serverSocket));
  // In the past, this would cause a SEGV
}

TEST(ThriftServer, useExistingSocketAndConnectionIdleTimeout) {
  // This is ConnectionIdleTimeoutTest, but with an existing socket
  TestThriftServerFactory<TestInterface> factory;
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());
  folly::AsyncServerSocket::UniquePtr serverSocket(
      new folly::AsyncServerSocket);
  serverSocket->bind(0);
  server->useExistingSocket(std::move(serverSocket));

  server->setIdleTimeout(std::chrono::milliseconds(20));
  apache::thrift::util::ScopedServerThread st(server);

  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *st.getAddress());

  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  std::string response;
  client.sync_sendResponse(response, 200);
  EXPECT_EQ(response, "test200");
  base.loop();
}

namespace {
class ReadCallbackTest : public folly::AsyncTransport::ReadCallback {
 public:
  void getReadBuffer(void**, size_t*) override {}
  void readDataAvailable(size_t) noexcept override {}
  void readEOF() noexcept override { eof = true; }

  void readErr(const folly::AsyncSocketException&) noexcept override {
    eof = true;
  }

  bool eof = false;
};
} // namespace

TEST(ThriftServer, ShutdownSocketSetTest) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());
  ScopedServerThread sst(server);
  folly::EventBase base;
  ReadCallbackTest cb;

  auto socket2 = folly::AsyncSocket::newSocket(&base, *sst.getAddress());
  socket2->setReadCB(&cb);

  base.tryRunAfterDelay(
      [&]() { folly::tryGetShutdownSocketSet()->shutdownAll(); }, 10);
  base.tryRunAfterDelay([&]() { base.terminateLoopSoon(); }, 30);
  base.loopForever();
  EXPECT_EQ(cb.eof, true);
}

TEST(ThriftServer, ShutdownDegenarateServer) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = factory.create();
  server->setMaxRequests(1);
  server->setNumIOWorkerThreads(1);
  ScopedServerThread sst(server);
}

TEST(ThriftServer, ModifyingIOThreadCountLive) {
  TestThriftServerFactory<TestInterface> factory;
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());
  auto iothreadpool = std::make_shared<folly::IOThreadPoolExecutor>(0);
  server->setIOThreadPool(iothreadpool);

  ScopedServerThread sst(server);
  // If there are no worker threads, generally the server event base
  // will stop loop()ing.  Create a timeout event to make sure
  // it continues to loop for the duration of the test.
  server->getServeEventBase()->runInEventBaseThread(
      [&]() { server->getServeEventBase()->tryRunAfterDelay([]() {}, 5000); });

  server->getServeEventBase()->runInEventBaseThreadAndWait(
      [=]() { iothreadpool->setNumThreads(0); });

  folly::EventBase base;

  auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());

  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  std::string response;

  boost::polymorphic_downcast<ClientChannel*>(client.getChannel())
      ->setTimeout(100);

  // This should fail as soon as it connects:
  // since AsyncServerSocket has no accept callbacks installed,
  // it should close the connection right away.
  ASSERT_ANY_THROW(client.sync_sendResponse(response, 64));

  server->getServeEventBase()->runInEventBaseThreadAndWait(
      [=]() { iothreadpool->setNumThreads(30); });

  auto socket2 = folly::AsyncSocket::newSocket(&base, *sst.getAddress());

  // Can't reuse client since the channel has gone bad
  TestServiceAsyncClient client2(
      HeaderClientChannel::newChannel(std::move(socket2)));

  client2.sync_sendResponse(response, 64);
}

TEST(ThriftServer, setIOThreadPool) {
  auto exe = std::make_shared<folly::IOThreadPoolExecutor>(1);
  TestThriftServerFactory<TestInterface> factory;
  factory.useSimpleThreadManager(false);
  auto server = std::static_pointer_cast<ThriftServer>(factory.create());

  // Set the exe, this used to trip various calls like
  // CHECK(ioThreadPool->numThreads() == 0).
  server->setIOThreadPool(exe);
  EXPECT_EQ(1, server->getNumIOWorkerThreads());
}

TEST(ThriftServer, IdleServerTimeout) {
  TestThriftServerFactory<TestInterface> factory;

  auto server = factory.create();
  auto thriftServer = dynamic_cast<ThriftServer*>(server.get());
  thriftServer->setIdleServerTimeout(std::chrono::milliseconds(50));

  ScopedServerThread scopedServer(server);
  scopedServer.join();
}

TEST(ThriftServer, ServerConfigTest) {
  ThriftServer server;

  wangle::ServerSocketConfig defaultConfig;
  // If nothing is set, expect defaults
  auto serverConfig = server.getServerSocketConfig();
  EXPECT_EQ(
      serverConfig.sslHandshakeTimeout, defaultConfig.sslHandshakeTimeout);

  // Idle timeout of 0 with no SSL handshake set, expect it to be 0.
  server.setIdleTimeout(std::chrono::milliseconds::zero());
  serverConfig = server.getServerSocketConfig();
  EXPECT_EQ(
      serverConfig.sslHandshakeTimeout, std::chrono::milliseconds::zero());

  // Expect the explicit to always win
  server.setSSLHandshakeTimeout(std::chrono::milliseconds(100));
  serverConfig = server.getServerSocketConfig();
  EXPECT_EQ(serverConfig.sslHandshakeTimeout, std::chrono::milliseconds(100));

  // Clear it and expect it to be zero again (due to idle timeout = 0)
  server.setSSLHandshakeTimeout(std::nullopt);
  serverConfig = server.getServerSocketConfig();
  EXPECT_EQ(
      serverConfig.sslHandshakeTimeout, std::chrono::milliseconds::zero());
}

TEST(ThriftServer, MultiPort) {
  class MultiPortThriftServer : public ThriftServer {
   public:
    using ServerBootstrap::getSockets;
  };

  auto server = std::make_shared<MultiPortThriftServer>();
  server->setInterface(std::make_shared<TestInterface>());
  server->setNumIOWorkerThreads(1);
  server->setNumCPUWorkerThreads(1);

  // Add two ports 0 to trigger listening on two random ports.
  folly::SocketAddress addr;
  addr.setFromLocalPort(static_cast<uint16_t>(0));
  server->setAddresses({addr, addr});

  ScopedServerThread t(server);

  auto sockets = server->getSockets();
  ASSERT_EQ(sockets.size(), 2);

  folly::SocketAddress addr1, addr2;
  sockets[0]->getAddress(&addr1);
  sockets[1]->getAddress(&addr2);

  EXPECT_NE(addr1.getPort(), addr2.getPort());

  // Test that we can talk via first port.
  folly::EventBase base;

  auto testFn = [&](folly::SocketAddress& address) {
    auto socket = folly::AsyncSocket::newSocket(&base, address);
    TestServiceAsyncClient client(
        HeaderClientChannel::newChannel(std::move(socket)));
    std::string response;
    client.sync_sendResponse(response, 42);
    EXPECT_EQ(response, "test42");
  };

  testFn(addr1);
  testFn(addr2);
}

TEST(ThriftServer, ClientIdentityHook) {
  /* Tests that the server calls the client identity hook when creating a new
     connection context */

  std::atomic<bool> flag{false};
  auto hook = [&flag](
                  const folly::AsyncTransport* /* unused */,
                  const X509* /* unused */,
                  const folly::SocketAddress& /* unused */) {
    flag = true;
    return std::unique_ptr<void, void (*)(void*)>(nullptr, [](void*) {});
  };

  TestThriftServerFactory<TestInterface> factory;
  auto server = factory.create();
  server->setClientIdentityHook(hook);
  apache::thrift::util::ScopedServerThread st(server);

  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *st.getAddress());
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));
  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_TRUE(flag);
}

namespace {
void setupServerSSL(ThriftServer& server) {
  auto sslConfig = std::make_shared<wangle::SSLContextConfig>();
  sslConfig->setCertificate(folly::kTestCert, folly::kTestKey, "");
  sslConfig->clientCAFile = folly::kTestCA;
  sslConfig->sessionContext = "ThriftServerTest";
  server.setSSLConfig(std::move(sslConfig));
}

std::shared_ptr<folly::SSLContext> makeClientSslContext() {
  auto ctx = std::make_shared<folly::SSLContext>();
  ctx->loadCertificate(folly::kTestCert);
  ctx->loadPrivateKey(folly::kTestKey);
  ctx->loadTrustedCertificates(folly::kTestCA);
  ctx->authenticate(
      true /* verify server cert */, false /* don't verify server name */);
  ctx->setVerificationOption(folly::SSLContext::SSLVerifyPeerEnum::VERIFY);
  return ctx;
}

void doBadRequestHeaderTest(bool duplex, bool secure) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setDuplex(duplex);
  if (secure) {
    setupServerSSL(*server);
  }
  ScopedServerThread sst(std::move(server));

  folly::EventBase evb;
  folly::AsyncSocket::UniquePtr socket(
      secure ? new folly::AsyncSSLSocket(makeClientSslContext(), &evb)
             : new folly::AsyncSocket(&evb));
  socket->connect(nullptr /* connect callback */, *sst.getAddress());

  class RecordWriteSuccessCallback
      : public folly::AsyncTransport::WriteCallback {
   public:
    void writeSuccess() noexcept override {
      EXPECT_FALSE(success_);
      success_.emplace(true);
    }

    void writeErr(
        size_t /* bytesWritten */,
        const folly::AsyncSocketException& /* exception */) noexcept override {
      EXPECT_FALSE(success_);
      success_.emplace(false);
    }

    bool success() const { return success_ && *success_; }

   private:
    folly::Optional<bool> success_;
  };
  RecordWriteSuccessCallback recordSuccessWriteCallback;

  class CheckClosedReadCallback : public folly::AsyncTransport::ReadCallback {
   public:
    explicit CheckClosedReadCallback(folly::AsyncSocket& socket)
        : socket_(socket) {
      socket_.setReadCB(this);
    }

    ~CheckClosedReadCallback() override {
      // We expect that the server closed the connection
      EXPECT_TRUE(remoteClosed_);
      socket_.close();
    }

    void getReadBuffer(void** bufout, size_t* lenout) override {
      // For this test, we never do anything with the buffered data, but we
      // still need to implement the full ReadCallback interface.
      *bufout = buf_;
      *lenout = sizeof(buf_);
    }

    void readDataAvailable(size_t /* len */) noexcept override {}

    void readEOF() noexcept override { remoteClosed_ = true; }

    void readErr(const folly::AsyncSocketException& ex) noexcept override {
      ASSERT_EQ(ECONNRESET, ex.getErrno());
      remoteClosed_ = true;
    }

   private:
    folly::AsyncSocket& socket_;
    char buf_[1024];
    bool remoteClosed_{false};
  };

  EXPECT_TRUE(socket->good());
  {
    CheckClosedReadCallback checkClosedReadCallback_(*socket);
    constexpr folly::StringPiece kBadRequest("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    socket->write(
        &recordSuccessWriteCallback, kBadRequest.data(), kBadRequest.size());
    evb.loop();
  }

  EXPECT_TRUE(recordSuccessWriteCallback.success());
  EXPECT_FALSE(socket->good());
}
} // namespace

TEST(ThriftServer, BadRequestHeaderNoDuplexNoSsl) {
  doBadRequestHeaderTest(false /* duplex */, false /* secure */);
}

TEST(ThriftServer, BadRequestHeaderDuplexNoSsl) {
  doBadRequestHeaderTest(true /* duplex */, false /* secure */);
}

TEST(ThriftServer, BadRequestHeaderNoDuplexSsl) {
  doBadRequestHeaderTest(false /* duplex */, true /* secure */);
}

TEST(ThriftServer, BadRequestHeaderDuplexSsl) {
  doBadRequestHeaderTest(true /* duplex */, true /* secure */);
}

TEST(ThriftServer, SSLRequiredRejectsPlaintext) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setSSLPolicy(SSLPolicy::REQUIRED);
  setupServerSSL(*server);
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  std::string response;
  EXPECT_THROW(client.sync_sendResponse(response, 64);, TTransportException);
}

namespace {
class FizzStopTLSConnector
    : public fizz::client::AsyncFizzClient::HandshakeCallback,
      public fizz::AsyncFizzBase::EndOfTLSCallback {
 public:
  folly::AsyncSocket::UniquePtr connect(
      const folly::SocketAddress& address, folly::EventBase* eb) {
    eb_ = eb;

    auto sock = folly::AsyncSocket::newSocket(eb_, address);
    auto ctx = std::make_shared<fizz::client::FizzClientContext>();
    ctx->setSupportedAlpns({"rs"});
    auto thriftParametersContext =
        std::make_shared<apache::thrift::ThriftParametersContext>();
    thriftParametersContext->setUseStopTLS(true);
    auto extension =
        std::make_shared<apache::thrift::ThriftParametersClientExtension>(
            thriftParametersContext);

    client_.reset(new fizz::client::AsyncFizzClient(
        std::move(sock), std::move(ctx), std::move(extension)));
    client_->connect(
        this,
        nullptr,
        folly::none,
        folly::none,
        folly::Optional<std::vector<fizz::ech::ECHConfig>>(folly::none),
        std::chrono::milliseconds(100));
    return promise_.getFuture().getVia(eb_);
  }

  void fizzHandshakeSuccess(
      fizz::client::AsyncFizzClient* client) noexcept override {
    client->setEndOfTLSCallback(this);
  }

  void fizzHandshakeError(
      fizz::client::AsyncFizzClient* /* unused */,
      folly::exception_wrapper ex) noexcept override {
    promise_.setException(ex);
    FAIL();
  }

  void endOfTLS(
      fizz::AsyncFizzBase* transport, std::unique_ptr<folly::IOBuf>) override {
    auto sock = transport->getUnderlyingTransport<folly::AsyncSocket>();
    DCHECK(sock);

    auto fd = sock->detachNetworkSocket();
    auto zcId = sock->getZeroCopyBufId();

    // create new socket
    auto plaintextTransport =
        folly::AsyncSocket::UniquePtr(new folly::AsyncSocket(eb_, fd, zcId));
    promise_.setValue(std::move(plaintextTransport));
  }

  fizz::client::AsyncFizzClient::UniquePtr client_;
  folly::Promise<folly::AsyncSocket::UniquePtr> promise_;
  folly::EventBase* eb_;
};
} // namespace

TEST(ThriftServer, StopTLSDowngrade) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setSSLPolicy(SSLPolicy::REQUIRED);
  auto sslConfig = std::make_shared<wangle::SSLContextConfig>();
  sslConfig->setNextProtocols({"rs"});
  sslConfig->setCertificate(folly::kTestCert, folly::kTestKey, "");
  sslConfig->clientVerification =
      folly::SSLContext::VerifyClientCertificate::DO_NOT_REQUEST;
  server->setSSLConfig(std::move(sslConfig));
  ThriftTlsConfig thriftConfig;
  thriftConfig.enableThriftParamsNegotiation = true;
  thriftConfig.enableStopTLS = true;
  server->setThriftConfig(thriftConfig);
  server->setAcceptorFactory(
      std::make_shared<DefaultThriftAcceptorFactory>(server.get()));
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  FizzStopTLSConnector connector;
  auto transport = connector.connect(*sst.getAddress(), &base);
  // Note we only use stop tls with rocket
  TestServiceAsyncClient client(
      RocketClientChannel::newChannel(std::move(transport)));

  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_EQ(response, "test64");
  base.loopOnce();
}

TEST(ThriftServer, SSLRequiredAllowsLocalPlaintext) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setAllowPlaintextOnLoopback(true);
  server->setSSLPolicy(SSLPolicy::REQUIRED);
  setupServerSSL(*server);
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  // ensure that the address is loopback
  auto port = sst.getAddress()->getPort();
  folly::SocketAddress loopback("::1", port);
  auto socket = folly::AsyncSocket::newSocket(&base, loopback);
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_EQ(response, "test64");
  base.loop();
}

TEST(ThriftServer, SSLRequiredLoopbackUsesSSL) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setAllowPlaintextOnLoopback(true);
  server->setSSLPolicy(SSLPolicy::REQUIRED);
  setupServerSSL(*server);
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  // ensure that the address is loopback
  auto port = sst.getAddress()->getPort();
  folly::SocketAddress loopback("::1", port);

  auto ctx = makeClientSslContext();
  auto sslSock = TAsyncSSLSocket::newSocket(ctx, &base);
  sslSock->connect(nullptr /* connect callback */, loopback);

  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(sslSock)));

  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_EQ(response, "test64");
  base.loop();
}

TEST(ThriftServer, SSLPermittedAcceptsPlaintextAndSSL) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setSSLPolicy(SSLPolicy::PERMITTED);
  setupServerSSL(*server);
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  {
    SCOPED_TRACE("Plaintext");
    auto socket = folly::AsyncSocket::newSocket(&base, *sst.getAddress());
    TestServiceAsyncClient client(
        HeaderClientChannel::newChannel(std::move(socket)));

    std::string response;
    client.sync_sendResponse(response, 64);
    EXPECT_EQ(response, "test64");
    base.loop();
  }

  {
    SCOPED_TRACE("SSL");
    auto ctx = makeClientSslContext();
    auto sslSock = TAsyncSSLSocket::newSocket(ctx, &base);
    sslSock->connect(nullptr /* connect callback */, *sst.getAddress());

    TestServiceAsyncClient client(
        HeaderClientChannel::newChannel(std::move(sslSock)));

    std::string response;
    client.sync_sendResponse(response, 64);
    EXPECT_EQ(response, "test64");
    base.loop();
  }
}

TEST(ThriftServer, ClientOnlyTimeouts) {
  class SendResponseInterface : public TestServiceSvIf {
    void sendResponse(std::string& _return, int64_t shouldSleepMs) override {
      auto header = getConnectionContext()->getHeader();
      if (shouldSleepMs) {
        usleep(shouldSleepMs * 1000);
      }
      _return = fmt::format(
          "{}:{}",
          header->getClientTimeout().count(),
          header->getClientQueueTimeout().count());
    }
  };
  TestThriftServerFactory<SendResponseInterface> factory;
  ScopedServerThread st(factory.create());

  folly::EventBase base;
  auto socket = folly::AsyncSocket::newSocket(&base, *st.getAddress());
  TestServiceAsyncClient client(
      HeaderClientChannel::newChannel(std::move(socket)));

  for (bool clientOnly : {false, true}) {
    for (bool shouldTimeOut : {true, false}) {
      std::string response;
      RpcOptions rpcOpts;
      rpcOpts.setTimeout(std::chrono::milliseconds(30));
      rpcOpts.setQueueTimeout(std::chrono::milliseconds(30));
      rpcOpts.setClientOnlyTimeouts(clientOnly);
      try {
        client.sync_sendResponse(rpcOpts, response, shouldTimeOut ? 50 : 0);
        EXPECT_FALSE(shouldTimeOut);
        if (clientOnly) {
          EXPECT_EQ(response, "0:0");
        } else {
          EXPECT_EQ(response, "30:30");
        }
      } catch (...) {
        EXPECT_TRUE(shouldTimeOut);
      }
    }
  }
  base.loop();
}

TEST(ThriftServer, QueueTimeoutStressTest) {
  // Make sure we only open one connection to the server.
  auto ioExecutor = std::make_shared<folly::IOThreadPoolExecutor>(1);
  folly::setIOExecutor(ioExecutor);

  static std::atomic<int> server_reply = 0;
  static std::atomic<int> received_reply = 0;

  class SendResponseInterface : public TestServiceSvIf {
    void sendResponse(std::string& _return, int64_t id) override {
      DCHECK(lastSeenId_ < id);

      if (lastSeenId_ + 1 == id) {
        std::this_thread::sleep_for(sleepTime_);
        sleepTime_ *= 2;
      } else {
        sleepTime_ = std::chrono::microseconds{1};
      }
      server_reply++;
      lastSeenId_ = id;
      _return = "wow";
    }

    std::chrono::microseconds sleepTime_{1};
    int64_t lastSeenId_{-1};
  };

  constexpr size_t kNumReqs = 50000;

  {
    ScopedServerInterfaceThread runner(
        std::make_shared<SendResponseInterface>());
    runner.getThriftServer().setQueueTimeout(std::chrono::milliseconds{10});

    auto client = runner.newClient<TestServiceAsyncClient>(
        nullptr /* executor */, [](auto socket) mutable {
          return RocketClientChannel::newChannel(std::move(socket));
        });

    std::vector<folly::SemiFuture<std::string>> futures;
    for (size_t req = 0; req < kNumReqs; ++req) {
      futures.emplace_back(client->semifuture_sendResponse(req));
    }
    size_t exceptions = 0;
    for (auto& future : futures) {
      auto t = std::move(future).getTry();
      if (t.hasValue()) {
        ++received_reply;
      } else {
        ++exceptions;
      }
    }

    EXPECT_LT(exceptions, kNumReqs);
    EXPECT_GT(exceptions, 0);
  }

  EXPECT_EQ(received_reply, server_reply);
}

TEST_P(HeaderOrRocket, PreprocessHeaders) {
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  folly::EventBase base;
  auto client = makeClient(runner, &base);

  runner.getThriftServer().setPreprocess([&](auto& params) -> PreprocessResult {
    auto p = folly::get_ptr(params.headers, "foo");
    if (!p) {
      ADD_FAILURE() << "expected to see header 'foo'";
    } else if (*p != "bar") {
      ADD_FAILURE() << "expected to see header with value 'bar'";
    }
    return {};
  });

  RpcOptions rpcOptions;
  rpcOptions.setWriteHeader("foo", "bar");
  client->sync_voidResponse(rpcOptions);
}

TEST_P(HeaderOrRocket, TaskTimeoutBeforeProcessing) {
  folly::Baton haltBaton;
  std::atomic<int> processedCount{0};

  class VoidResponseInterface : public TestServiceSvIf {
   public:
    VoidResponseInterface() = delete;
    VoidResponseInterface(
        folly::Baton<>& haltBaton, std::atomic<int>& processedCount)
        : haltBaton_{haltBaton}, processedCount_{processedCount} {}

    void voidResponse() override {
      processedCount_++;
      haltBaton_.wait();
    }

   private:
    folly::Baton<>& haltBaton_;
    std::atomic<int>& processedCount_;
  };

  {
    ScopedServerInterfaceThread runner(
        std::make_shared<VoidResponseInterface>(haltBaton, processedCount),
        "::1",
        0,
        [](auto& server) {
          // Set task timeout and disable queue timeout
          server.setQueueTimeout(0ms);
          server.setTaskExpireTime(10ms);
          server.setUseClientTimeout(false);
        });
    auto client = makeClient(runner, folly::getEventBase());

    // Make two requests and test that they time out
    for (int i = 0; i < 2; ++i) {
      folly::fibers::Baton baton;
      THeader th;
      folly::exception_wrapper ew;
      client->voidResponse(ServerErrorCallback::create(baton, th, ew));
      baton.wait();
      bool matched = ew.with_exception([](const TApplicationException& tae) {
        EXPECT_EQ(TApplicationException::TIMEOUT, tae.getType());
      });
      ASSERT_TRUE(matched);
      EXPECT_EQ(*folly::get_ptr(th.getHeaders(), "ex"), kTaskExpiredErrorCode);
    }
    haltBaton.post();
  }

  // Assert only one request (the first) was processed
  EXPECT_EQ(processedCount, 1);
}

TEST(ThriftServer, RocketOverSSLNoALPN) {
  auto server = std::static_pointer_cast<ThriftServer>(
      TestThriftServerFactory<TestInterface>().create());
  server->setSSLPolicy(SSLPolicy::REQUIRED);
  setupServerSSL(*server);
  ScopedServerThread sst(std::move(server));

  folly::EventBase base;
  auto port = sst.getAddress()->getPort();
  folly::SocketAddress loopback("::1", port);

  auto ctx = makeClientSslContext();
  folly::AsyncSSLSocket::UniquePtr sslSock(
      new folly::AsyncSSLSocket(ctx, &base));
  sslSock->connect(nullptr /* connect callback */, loopback);

  TestServiceAsyncClient client(
      RocketClientChannel::newChannel(std::move(sslSock)));

  std::string response;
  client.sync_sendResponse(response, 64);
  EXPECT_EQ(response, "test64");
}

TEST(ThriftServer, SocketQueueTimeout) {
  TestThriftServerFactory<TestServiceSvIf> factory;
  auto baseServer = factory.create();

  auto checkSocketQueueTimeout = [&](std::chrono::nanoseconds expectedTimeout) {
    auto server = std::dynamic_pointer_cast<ThriftServer>(baseServer);
    ASSERT_NE(server, nullptr);
    const auto sockets = server->getSockets();
    EXPECT_GT(sockets.size(), 0);
    for (auto& socket : sockets) {
      // Reliably inducing the socket queue timeout is non-trivial through
      // the public API of ThriftServer. Instead, we just need to ensure
      // that each socket has the correct queue timeout after the
      // ThriftServer is set up. The underlying timeout behavior is covered
      // by AsyncServerSocket tests.
      EXPECT_EQ(*socket->getQueueTimeout(), expectedTimeout);
    }
  };

  constexpr auto kDefaultTimeout = 10ms;
  constexpr auto kThriftFlagObserverTimeout = 20ms;
  constexpr auto kBaselineTimeout = 30ms;
  constexpr auto kOverrideTimeout = 40ms;
  THRIFT_FLAG_SET_MOCK(
      server_default_socket_queue_timeout_ms, kDefaultTimeout.count());

  ScopedServerThread st(baseServer);

  // Should fall back to thrift flag by default
  checkSocketQueueTimeout(kDefaultTimeout);

  // Should trigger thrift flag observer
  THRIFT_FLAG_SET_MOCK(
      server_default_socket_queue_timeout_ms,
      kThriftFlagObserverTimeout.count());
  folly::observer_detail::ObserverManager::waitForAllUpdates();
  checkSocketQueueTimeout(kThriftFlagObserverTimeout);

  // Should use config instead of thrift flag
  baseServer->setSocketQueueTimeout(
      kBaselineTimeout, AttributeSource::BASELINE);
  folly::observer_detail::ObserverManager::waitForAllUpdates();
  checkSocketQueueTimeout(kBaselineTimeout);

  // Should use override instead of config
  baseServer->setSocketQueueTimeout(kOverrideTimeout);
  checkSocketQueueTimeout(kOverrideTimeout);

  THRIFT_FLAG_SET_MOCK(
      server_default_socket_queue_timeout_ms, kDefaultTimeout.count());
  folly::observer_detail::ObserverManager::waitForAllUpdates();

  // Should go back to config instead of override
  baseServer->setSocketQueueTimeout(folly::none);
  checkSocketQueueTimeout(kBaselineTimeout);

  // Should go back to using thrift flag instead of flag
  baseServer->setSocketQueueTimeout(folly::none, AttributeSource::BASELINE);
  folly::observer_detail::ObserverManager::waitForAllUpdates();
  checkSocketQueueTimeout(kDefaultTimeout);
}

TEST_P(HeaderOrRocket, setMaxReuqestsToOne) {
  ScopedServerInterfaceThread runner(
      std::make_shared<TestInterface>(), "::1", 0, [](auto&& server) {
        server.setMaxRequests(1);
      });
  auto client = makeClient(runner, nullptr);
  EXPECT_EQ(client->semifuture_sendResponse(42).get(), "test42");
}

namespace {

folly::observer::SimpleObservable<AdaptiveConcurrencyController::Config>
    oConfig{AdaptiveConcurrencyController::Config{}};

THRIFT_PLUGGABLE_FUNC_SET(
    folly::observer::Observer<
        apache::thrift::AdaptiveConcurrencyController::Config>,
    makeAdaptiveConcurrencyConfig) {
  return oConfig.getObserver();
}

static auto makeConfig(size_t concurrency, double jitter = 0.0) {
  AdaptiveConcurrencyController::Config config;
  config.minConcurrency = concurrency;
  config.recalcPeriodJitter = jitter;
  return config;
}

void setConfig(size_t concurrency, double jitter = 0.0) {
  oConfig.setValue(makeConfig(concurrency, jitter));
  folly::observer_detail::ObserverManager::waitForAllUpdates();
}
} // namespace

TEST_P(HeaderOrRocket, AdaptiveConcurrencyConfig) {
  class TestInterface : public TestServiceSvIf {
   public:
    void voidResponse() override {}
  };

  folly::EventBase base;
  ScopedServerInterfaceThread runner(std::make_shared<TestInterface>());
  runner.getThriftServer().setMaxRequests(5000);
  EXPECT_EQ(runner.getThriftServer().getMaxRequests(), 5000);
  auto& controller = runner.getThriftServer().adaptiveConcurrencyController();
  EXPECT_FALSE(controller.enabled());
  auto client = makeClient(runner, &base);

  setConfig(20, 0);

  // controller will enforce minconcurrency after first request
  EXPECT_FALSE(controller.enabled());
  client->sync_voidResponse();
  EXPECT_TRUE(controller.enabled());
  EXPECT_EQ(runner.getThriftServer().getMaxRequests(), 20);
  // verify controller's limit overrides explicit limit on the server
  runner.getThriftServer().setMaxRequests(2000);
  EXPECT_EQ(runner.getThriftServer().getMaxRequests(), 20);

  // verify disabling conroller causes the explicit limit to take effect
  setConfig(0, 0);
  EXPECT_FALSE(controller.enabled());
  EXPECT_EQ(runner.getThriftServer().getMaxRequests(), 2000);
}

TEST_P(HeaderOrRocket, OnStartStopServingTest) {
  class TestInterface : public TestServiceSvIf {
   public:
    folly::Baton<> startEnter, startExit;
    folly::Baton<> stopEnter, stopExit;

    void voidResponse() override {}

    void echoRequest(std::string& result, std::unique_ptr<std::string> req) {
      result = std::move(*req);
    }

    folly::SemiFuture<folly::Unit> semifuture_onStartServing() override {
      return folly::makeSemiFuture().deferValue([this](folly::Unit) {
        startEnter.post();
        startExit.wait();
      });
    }

    folly::SemiFuture<folly::Unit> semifuture_onStopServing() override {
      return folly::makeSemiFuture().deferValue([this](folly::Unit) {
        stopEnter.post();
        stopExit.wait();
      });
    }
  };

  auto testIf = std::make_shared<TestInterface>();

  class TestEventHandler : public server::TServerEventHandler {
   public:
    void preStart(const folly::SocketAddress* address) override {
      this->address = *address;
      preStartEnter.post();
      preStartExit.wait();
    }
    folly::Baton<> preStartEnter, preStartExit;
    folly::SocketAddress address;
  };
  auto preStartHandler = std::make_shared<TestEventHandler>();

  std::unique_ptr<ScopedServerInterfaceThread> runner;

  folly::Baton<> serverSetupBaton;
  std::thread startRunnerThread([&] {
    runner = std::make_unique<ScopedServerInterfaceThread>(
        testIf, "::1", 0, [&](auto& ts) {
          auto tf = std::make_shared<PosixThreadFactory>(
              PosixThreadFactory::ATTACHED);
          // We need at least 2 threads for the test
          auto tm = ThreadManager::newSimpleThreadManager(2);
          tm->threadFactory(move(tf));
          tm->start();
          ts.setThreadManager(tm);
          ts.addServerEventHandler(preStartHandler);
          ts.setInternalMethods({"voidResponse"});
          ts.setRejectRequestsUntilStarted(true);
          serverSetupBaton.post();
        });
  });

  serverSetupBaton.wait();

  // Wait for preStart callback
  EXPECT_TRUE(preStartHandler->preStartEnter.try_wait_for(2s));
  TestServiceAsyncClient client(
      apache::thrift::PooledRequestChannel::newSyncChannel(
          folly::getUnsafeMutableGlobalIOExecutor(),
          [address = preStartHandler->address,
           this](folly::EventBase& eb) mutable {
            return makeChannel(folly::AsyncSocket::UniquePtr(
                new folly::AsyncSocket(&eb, address)));
          }));

  client.semifuture_voidResponse().get();
  EXPECT_THROW(
      client.semifuture_echoRequest("echo").get(), TApplicationException);
  EXPECT_FALSE(testIf->startEnter.ready());
  preStartHandler->preStartExit.post();

  // Wait for onStartServing()
  EXPECT_TRUE(testIf->startEnter.try_wait_for(2s));
  client.semifuture_voidResponse().get();
  EXPECT_THROW(
      client.semifuture_echoRequest("echo").get(), TApplicationException);
  testIf->startExit.post();

  startRunnerThread.join();
  // Wait until server is marked as started.
  for (size_t retry = 0; retry < 10; ++retry) {
    try {
      auto echo = client.semifuture_echoRequest("echo").get();
      EXPECT_EQ("echo", echo);
      break;
    } catch (const TApplicationException&) {
      std::this_thread::sleep_for(std::chrono::milliseconds{100});
    }
  }

  client.semifuture_voidResponse().get();
  EXPECT_EQ("echo", client.semifuture_echoRequest("echo").get());

  runner->getThriftServer().setEnabled(false);
  client.semifuture_voidResponse().get();
  EXPECT_THROW(
      client.semifuture_echoRequest("echo").get(), TApplicationException);

  runner->getThriftServer().setEnabled(true);
  client.semifuture_voidResponse().get();
  EXPECT_EQ("echo", client.semifuture_echoRequest("echo").get());

  folly::Baton<> backgroundEnter, backgroundExit;

  auto backgroundTask = [&]() -> folly::coro::Task<void> {
    backgroundEnter.post();
    EXPECT_TRUE(backgroundExit.try_wait_for(2s));
    // Wait for cancellation
    const folly::CancellationToken& ct =
        co_await folly::coro::co_current_cancellation_token;
    for (size_t retry = 0; retry < 20 && !ct.isCancellationRequested();
         retry++) {
      co_await folly::coro::sleepReturnEarlyOnCancel(100ms);
    }
    EXPECT_TRUE(ct.isCancellationRequested());
    co_return;
  };

  auto& server = dynamic_cast<ThriftServer&>(runner->getThriftServer());
  server.getAsyncScope().add(
      backgroundTask().scheduleOn(server.getThreadManager().get()));
  // Wait for backgroundTask to start
  EXPECT_TRUE(backgroundEnter.try_wait_for(2s));
  client.semifuture_voidResponse().get();
  backgroundExit.post();

  // Stop the server on a different thread
  folly::getGlobalIOExecutor()->getEventBase()->runInEventBaseThread(
      [&runner]() { runner.reset(); });

  // Wait for onStopServing()
  EXPECT_TRUE(testIf->stopEnter.try_wait_for(2s));
  client.semifuture_voidResponse().get();
  testIf->stopExit.post();
}

namespace {
enum class ProcessorImplementation {
  Containment,
  ContainmentLegacy,
  Inheritance
};
} // namespace

class HeaderOrRocketCompression
    : public HeaderOrRocketTest,
      public ::testing::WithParamInterface<
          std::tuple<TransportType, Compression, ProcessorImplementation>> {
 public:
  ProcessorImplementation processorImplementation =
      ProcessorImplementation::Containment;

  void SetUp() override {
    std::tie(transport, compression, processorImplementation) = GetParam();
  }

  std::unique_ptr<AsyncProcessorFactory> makeFactory() {
    // processor can only check for compressed request payload on rocket
    if (compression == Compression::Enabled &&
        transport == TransportType::Rocket) {
      return std::make_unique<CompressionCheckTestInterface>(
          processorImplementation, CompressionAlgorithm::ZSTD);
    } else {
      return std::make_unique<CompressionCheckTestInterface>(
          processorImplementation, CompressionAlgorithm::NONE);
    }
  }

 private:
  // Custom processor derived from AsyncProcessor with compressed request API
  struct ContainmentCompressionCheckProcessor : public AsyncProcessor {
    ContainmentCompressionCheckProcessor(
        std::unique_ptr<AsyncProcessor> underlyingProcessor,
        CompressionAlgorithm compression)
        : underlyingProcessor_(std::move(underlyingProcessor)),
          compression_(compression) {}
    void processSerializedRequest(
        ResponseChannelRequest::UniquePtr req,
        SerializedRequest&& serializedRequest,
        protocol::PROTOCOL_TYPES prot,
        Cpp2RequestContext* ctx,
        folly::EventBase* eb,
        concurrency::ThreadManager* tm) override {
      ADD_FAILURE() << "processSerializedRequest should not be called if "
                    << "processSerializedCompressedRequest is implemented";
      underlyingProcessor_->processSerializedRequest(
          std::move(req), std::move(serializedRequest), prot, ctx, eb, tm);
    }
    void processSerializedCompressedRequest(
        ResponseChannelRequest::UniquePtr req,
        SerializedCompressedRequest&& serializedRequest,
        protocol::PROTOCOL_TYPES prot,
        Cpp2RequestContext* ctx,
        folly::EventBase* eb,
        concurrency::ThreadManager* tm) override {
      // check that SerializedCompressedRequest has expected compression
      EXPECT_EQ(compression_, serializedRequest.getCompressionAlgorithm());
      underlyingProcessor_->processSerializedCompressedRequest(
          std::move(req), std::move(serializedRequest), prot, ctx, eb, tm);
    }
    std::unique_ptr<AsyncProcessor> underlyingProcessor_;
    CompressionAlgorithm compression_;
  };

  // Custom processor derived from AsyncProcessor without compressed request API
  struct LegacyContainmentProcessor : public AsyncProcessor {
    explicit LegacyContainmentProcessor(
        std::unique_ptr<AsyncProcessor> underlyingProcessor)
        : underlyingProcessor_(std::move(underlyingProcessor)) {}
    void processSerializedRequest(
        ResponseChannelRequest::UniquePtr req,
        SerializedRequest&& serializedRequest,
        protocol::PROTOCOL_TYPES prot,
        Cpp2RequestContext* ctx,
        folly::EventBase* eb,
        concurrency::ThreadManager* tm) override {
      underlyingProcessor_->processSerializedRequest(
          std::move(req), std::move(serializedRequest), prot, ctx, eb, tm);
    }
    std::unique_ptr<AsyncProcessor> underlyingProcessor_;
  };

  // Custom processor derived from generated processor
  struct InheritanceCompressionCheckProcessor
      : public TestInterface::ProcessorType {
    InheritanceCompressionCheckProcessor(
        TestServiceSvIf* iface, CompressionAlgorithm compression)
        : TestInterface::ProcessorType(iface), compression_(compression) {}
    void processSerializedCompressedRequest(
        ResponseChannelRequest::UniquePtr req,
        SerializedCompressedRequest&& serializedRequest,
        protocol::PROTOCOL_TYPES prot,
        Cpp2RequestContext* ctx,
        folly::EventBase* eb,
        concurrency::ThreadManager* tm) override {
      // check that SerializedCompressedRequest has expected compression
      EXPECT_EQ(compression_, serializedRequest.getCompressionAlgorithm());
      TestInterface::ProcessorType::processSerializedCompressedRequest(
          std::move(req), std::move(serializedRequest), prot, ctx, eb, tm);
    }
    CompressionAlgorithm compression_;
  };

  struct CompressionCheckTestInterface : public TestInterface {
    CompressionCheckTestInterface(
        ProcessorImplementation processorImplementation,
        CompressionAlgorithm compression)
        : processorImplementation_(processorImplementation),
          compression_(compression) {}
    std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override {
      switch (processorImplementation_) {
        case ProcessorImplementation::Containment:
          return std::make_unique<ContainmentCompressionCheckProcessor>(
              std::make_unique<TestInterface::ProcessorType>(this),
              compression_);
        case ProcessorImplementation::ContainmentLegacy:
          return std::make_unique<LegacyContainmentProcessor>(
              std::make_unique<TestInterface::ProcessorType>(this));
        case ProcessorImplementation::Inheritance:
          return std::make_unique<InheritanceCompressionCheckProcessor>(
              this, compression_);
      }
    }

    CreateMethodMetadataResult createMethodMetadata() override {
      // TODO(praihan) Restore the default implementation once we have migrated
      // the processor implementation.
      return {};
    }

    ProcessorImplementation processorImplementation_;
    CompressionAlgorithm compression_;
  };
};

TEST_P(HeaderOrRocketCompression, ClientCompressionTest) {
  folly::EventBase base;
  ScopedServerInterfaceThread runner(makeFactory());
  auto client = makeClient(runner, &base);

  std::string response;
  client->sync_sendResponse(response, 64);
  EXPECT_EQ(response, "test64");
}

INSTANTIATE_TEST_CASE_P(
    HeaderOrRocketCompression,
    HeaderOrRocketCompression,
    ::testing::Combine(
        testing::Values(TransportType::Header, TransportType::Rocket),
        testing::Values(Compression::Enabled, Compression::Disabled),
        testing::Values(
            ProcessorImplementation::Containment,
            ProcessorImplementation::ContainmentLegacy,
            ProcessorImplementation::Inheritance)));
