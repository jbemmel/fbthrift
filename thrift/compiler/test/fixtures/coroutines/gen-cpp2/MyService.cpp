/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift/compiler/test/fixtures/coroutines/gen-cpp2/MyService.h"
#include "thrift/compiler/test/fixtures/coroutines/gen-cpp2/MyService.tcc"
#include "thrift/compiler/test/fixtures/coroutines/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> MyServiceSvIf::getProcessor() {
  return std::make_unique<MyServiceAsyncProcessor>(this);
}


void MyServiceSvIf::ping() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("ping");
}

folly::SemiFuture<folly::Unit> MyServiceSvIf::semifuture_ping() {
  return apache::thrift::detail::si::semifuture([&] {
    return ping();
  });
}

folly::Future<folly::Unit> MyServiceSvIf::future_ping() {
  return apache::thrift::detail::si::future(semifuture_ping(), getThreadManager());
}

#if FOLLY_HAS_COROUTINES
folly::coro::Task<void> MyServiceSvIf::co_ping() {
  auto future = future_ping();
  return apache::thrift::detail::si::future_to_task(std::move(future));
}

folly::coro::Task<void> MyServiceSvIf::co_ping(apache::thrift::RequestParams /* params */) {
  return co_ping();
}
#endif // FOLLY_HAS_COROUTINES

void MyServiceSvIf::async_tm_ping(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
#if FOLLY_HAS_COROUTINES
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we have to
  // set them up now. This is just a short-term shim; in the long run, we
  // shouldn't generate the future, semifuture, and synchronous member functions
  // for entry points that explicitly ask for coroutines.
  apache::thrift::detail::si::async_tm_prep(this, callback.get());
  apache::thrift::RequestParams params{callback->getConnectionContext(),
    callback->getThreadManager(), callback->getEventBase()};
  try {
    apache::thrift::detail::si::async_tm_coro_start(
      co_ping(params),
      params.getThreadManager(),
      std::move(callback));
  } catch (...) {
    callback->exception(std::current_exception());
  }
#else // FOLLY_HAS_COROUTINES
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_ping();
  });
#endif // FOLLY_HAS_COROUTINES
}

void MyServiceSvIf::getRandomData(::std::string& /*_return*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getRandomData");
}

folly::SemiFuture<std::unique_ptr<::std::string>> MyServiceSvIf::semifuture_getRandomData() {
  return apache::thrift::detail::si::semifuture_returning_uptr([&](::std::string& _return) { getRandomData(_return); });
}

folly::Future<std::unique_ptr<::std::string>> MyServiceSvIf::future_getRandomData() {
  return apache::thrift::detail::si::future(semifuture_getRandomData(), getThreadManager());
}


void MyServiceSvIf::async_tm_getRandomData(std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<::std::string>>> callback) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_getRandomData();
  });
}

bool MyServiceSvIf::hasDataById(int64_t /*id*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("hasDataById");
}

folly::SemiFuture<bool> MyServiceSvIf::semifuture_hasDataById(int64_t id) {
  return apache::thrift::detail::si::semifuture([&] {
    return hasDataById(id);
  });
}

folly::Future<bool> MyServiceSvIf::future_hasDataById(int64_t id) {
  return apache::thrift::detail::si::future(semifuture_hasDataById(id), getThreadManager());
}

#if FOLLY_HAS_COROUTINES
folly::coro::Task<bool> MyServiceSvIf::co_hasDataById(int64_t id) {
  auto future = future_hasDataById(id);
  return apache::thrift::detail::si::future_to_task(std::move(future));
}

folly::coro::Task<bool> MyServiceSvIf::co_hasDataById(apache::thrift::RequestParams /* params */, int64_t id) {
  return co_hasDataById(id);
}
#endif // FOLLY_HAS_COROUTINES

void MyServiceSvIf::async_tm_hasDataById(std::unique_ptr<apache::thrift::HandlerCallback<bool>> callback, int64_t id) {
#if FOLLY_HAS_COROUTINES
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we have to
  // set them up now. This is just a short-term shim; in the long run, we
  // shouldn't generate the future, semifuture, and synchronous member functions
  // for entry points that explicitly ask for coroutines.
  apache::thrift::detail::si::async_tm_prep(this, callback.get());
  apache::thrift::RequestParams params{callback->getConnectionContext(),
    callback->getThreadManager(), callback->getEventBase()};
  try {
    apache::thrift::detail::si::async_tm_coro_start(
      co_hasDataById(params, id),
      params.getThreadManager(),
      std::move(callback));
  } catch (...) {
    callback->exception(std::current_exception());
  }
#else // FOLLY_HAS_COROUTINES
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_hasDataById(id);
  });
#endif // FOLLY_HAS_COROUTINES
}

void MyServiceSvIf::getDataById(::std::string& /*_return*/, int64_t /*id*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("getDataById");
}

folly::SemiFuture<std::unique_ptr<::std::string>> MyServiceSvIf::semifuture_getDataById(int64_t id) {
  return apache::thrift::detail::si::semifuture_returning_uptr([&](::std::string& _return) { getDataById(_return, id); });
}

folly::Future<std::unique_ptr<::std::string>> MyServiceSvIf::future_getDataById(int64_t id) {
  return apache::thrift::detail::si::future(semifuture_getDataById(id), getThreadManager());
}

#if FOLLY_HAS_COROUTINES
folly::coro::Task<std::unique_ptr<::std::string>> MyServiceSvIf::co_getDataById(int64_t id) {
  auto future = future_getDataById(id);
  return apache::thrift::detail::si::future_to_task(std::move(future));
}

folly::coro::Task<std::unique_ptr<::std::string>> MyServiceSvIf::co_getDataById(apache::thrift::RequestParams /* params */, int64_t id) {
  return co_getDataById(id);
}
#endif // FOLLY_HAS_COROUTINES

void MyServiceSvIf::async_eb_getDataById(std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<::std::string>>> callback, int64_t id) {
#if FOLLY_HAS_COROUTINES
  apache::thrift::RequestParams params{callback->getConnectionContext(),
    callback->getThreadManager(), callback->getEventBase()};
  try {
    apache::thrift::detail::si::async_eb_coro_start(
      co_getDataById(params, id),
      params.getThreadManager(),
      std::move(callback));
  } catch (...) {
    callback->exception(std::current_exception());
  }
#else // FOLLY_HAS_COROUTINES
  apache::thrift::detail::si::async_eb(this, std::move(callback), [this, id]() mutable {
    return future_getDataById(id);
  });
#endif // FOLLY_HAS_COROUTINES
}

void MyServiceSvIf::putDataById(int64_t /*id*/, std::unique_ptr<::std::string> /*data*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("putDataById");
}

folly::SemiFuture<folly::Unit> MyServiceSvIf::semifuture_putDataById(int64_t id, std::unique_ptr<::std::string> data) {
  return apache::thrift::detail::si::semifuture([&] {
    return putDataById(id, std::move(data));
  });
}

folly::Future<folly::Unit> MyServiceSvIf::future_putDataById(int64_t id, std::unique_ptr<::std::string> data) {
  return apache::thrift::detail::si::future(semifuture_putDataById(id, std::move(data)), getThreadManager());
}


void MyServiceSvIf::async_tm_putDataById(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback, int64_t id, std::unique_ptr<::std::string> data) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_putDataById(id, std::move(data));
  });
}

void MyServiceSvNull::ping() {
  return;
}

void MyServiceSvNull::getRandomData(::std::string& /*_return*/) {}

bool MyServiceSvNull::hasDataById(int64_t /*id*/) {
  return 0;
}

void MyServiceSvNull::putDataById(int64_t /*id*/, std::unique_ptr<::std::string> /*data*/) {
  return;
}

const char* MyServiceAsyncProcessor::getServiceName() {
  return "MyService";
}

void MyServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<MyServiceSvIf>::gen(response.metadata, response.context);
}

void MyServiceAsyncProcessor::processSerializedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> MyServiceAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const MyServiceAsyncProcessor::ProcessMap& MyServiceAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const MyServiceAsyncProcessor::ProcessMap MyServiceAsyncProcessor::binaryProcessMap_ {
  {"ping", &MyServiceAsyncProcessor::_processInThread_ping<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"getRandomData", &MyServiceAsyncProcessor::_processInThread_getRandomData<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"hasDataById", &MyServiceAsyncProcessor::_processInThread_hasDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"getDataById", &MyServiceAsyncProcessor::process_getDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"putDataById", &MyServiceAsyncProcessor::_processInThread_putDataById<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const MyServiceAsyncProcessor::ProcessMap& MyServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const MyServiceAsyncProcessor::ProcessMap MyServiceAsyncProcessor::compactProcessMap_ {
  {"ping", &MyServiceAsyncProcessor::_processInThread_ping<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"getRandomData", &MyServiceAsyncProcessor::_processInThread_getRandomData<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"hasDataById", &MyServiceAsyncProcessor::_processInThread_hasDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"getDataById", &MyServiceAsyncProcessor::process_getDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"putDataById", &MyServiceAsyncProcessor::_processInThread_putDataById<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

} // cpp2
