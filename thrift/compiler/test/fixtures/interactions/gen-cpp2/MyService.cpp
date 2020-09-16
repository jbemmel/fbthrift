/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift/compiler/test/fixtures/interactions/gen-cpp2/MyService.h"
#include "thrift/compiler/test/fixtures/interactions/gen-cpp2/MyService.tcc"
#include "thrift/compiler/test/fixtures/interactions/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace cpp2 {
std::unique_ptr<apache::thrift::AsyncProcessor> MyServiceSvIf::getProcessor() {
  return std::make_unique<MyServiceAsyncProcessor>(this);
}

std::unique_ptr<MyServiceSvIf::MyInteractionIf> MyServiceSvIf::createMyInteraction() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("createMyInteraction");
}

void MyServiceSvIf::foo() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("foo");
}

folly::SemiFuture<folly::Unit> MyServiceSvIf::semifuture_foo() {
  return apache::thrift::detail::si::semifuture([&] {
    return foo();
  });
}

folly::Future<folly::Unit> MyServiceSvIf::future_foo() {
  return apache::thrift::detail::si::future(semifuture_foo(), getThreadManager());
}

void MyServiceSvIf::async_tm_foo(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_foo();
  });
}

void MyServiceSvNull::foo() {
  return;
}



#if FOLLY_HAS_COROUTINES
folly::coro::Task<void> MyServiceSvIf::MyInteractionIf::co_frobnicate() {
  co_yield folly::coro::co_error(apache::thrift::TApplicationException("Function frobnicate is unimplemented"));
}

folly::coro::Task<void> MyServiceSvIf::MyInteractionIf::co_frobnicate(apache::thrift::RequestParams /* params */) {
  return co_frobnicate();
}
#endif // FOLLY_HAS_COROUTINES
void MyServiceSvIf::MyInteractionIf::async_tm_frobnicate(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
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
      co_frobnicate(params),
      params.getThreadManager(),
      std::move(callback));
  } catch (...) {
    callback->exception(std::current_exception());
  }
#else // FOLLY_HAS_COROUTINES
  callback->exception(apache::thrift::TApplicationException("Function frobnicate is unimplemented"));
#endif // FOLLY_HAS_COROUTINES
}

const char* MyServiceAsyncProcessor::getServiceName() {
  return "MyService";
}

void MyServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<MyServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
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
  {"foo", &MyServiceAsyncProcessor::_processInThread_foo<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"MyInteraction.frobnicate", &MyServiceAsyncProcessor::_processInThread_MyInteraction_frobnicate<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const MyServiceAsyncProcessor::ProcessMap& MyServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const MyServiceAsyncProcessor::ProcessMap MyServiceAsyncProcessor::compactProcessMap_ {
  {"foo", &MyServiceAsyncProcessor::_processInThread_foo<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"MyInteraction.frobnicate", &MyServiceAsyncProcessor::_processInThread_MyInteraction_frobnicate<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

const MyServiceAsyncProcessor::InteractionConstructorMap& MyServiceAsyncProcessor::getInteractionConstructorMap() {
  return interactionConstructorMap_;
}

const MyServiceAsyncProcessor::InteractionConstructorMap MyServiceAsyncProcessor::interactionConstructorMap_ {
  {"MyInteraction", &MyServiceAsyncProcessor::createMyInteraction},
};

std::unique_ptr<Tile> MyServiceAsyncProcessor::createInteractionImpl(const std::string& name) {
  const auto& cmap = getInteractionConstructorMap();
  auto fn = cmap.find(name);
  if (fn == cmap.end()) {
    LOG(ERROR) << "Unknown interaction name " << name;
    return std::make_unique<ErrorTile>(
                folly::make_exception_wrapper<TApplicationException>(
                    TApplicationException::TApplicationExceptionType::
                        INTERACTION_ERROR,
                    "Unknown interaction"));
  }
  return (this->*(fn->second))();
}} // cpp2
