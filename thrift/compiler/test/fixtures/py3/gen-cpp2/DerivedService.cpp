/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */

#include "thrift/compiler/test/fixtures/py3/gen-cpp2/DerivedService.h"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/DerivedService.tcc"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace py3 { namespace simple {
std::unique_ptr<apache::thrift::AsyncProcessor> DerivedServiceSvIf::getProcessor() {
  return std::make_unique<DerivedServiceAsyncProcessor>(this);
}

DerivedServiceSvIf::CreateMethodMetadataResult DerivedServiceSvIf::createMethodMetadata() {
  return ::apache::thrift::detail::ap::createMethodMetadataMap<DerivedServiceAsyncProcessor>();
}


::std::int32_t DerivedServiceSvIf::get_six() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("get_six");
}

folly::SemiFuture<::std::int32_t> DerivedServiceSvIf::semifuture_get_six() {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_get_six.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  return get_six();
}

folly::Future<::std::int32_t> DerivedServiceSvIf::future_get_six() {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_get_six.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_get_six(), getInternalKeepAlive());
}

void DerivedServiceSvIf::async_tm_get_six(std::unique_ptr<apache::thrift::HandlerCallback<::std::int32_t>> callback) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_get_six.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_get_six.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_get_six();
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_get_six();
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        callback->result(get_six());
        return;
      }
      default:
      {
        folly::assume_unreachable();
      }
    }
  } catch (...) {
    callback->exception(std::current_exception());
  }
}

::std::int32_t DerivedServiceSvNull::get_six() {
  return 0;
}



const char* DerivedServiceAsyncProcessor::getServiceName() {
  return "DerivedService";
}

void DerivedServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<DerivedServiceSvIf>::gen(response);
}

void DerivedServiceAsyncProcessor::processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

void DerivedServiceAsyncProcessor::processSerializedCompressedRequestWithMetadata(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), methodMetadata, protType, context, eb, tm);
}

const DerivedServiceAsyncProcessor::ProcessMap& DerivedServiceAsyncProcessor::getOwnProcessMap() {
  return kOwnProcessMap_;
}

const DerivedServiceAsyncProcessor::ProcessMap DerivedServiceAsyncProcessor::kOwnProcessMap_ {
  {"get_six", {&DerivedServiceAsyncProcessor::setUpAndProcess_get_six<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &DerivedServiceAsyncProcessor::setUpAndProcess_get_six<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
};

}} // py3::simple
