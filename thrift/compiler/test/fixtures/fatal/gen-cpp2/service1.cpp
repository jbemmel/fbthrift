/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */

#include "thrift/compiler/test/fixtures/fatal/gen-cpp2/service1.h"
#include "thrift/compiler/test/fixtures/fatal/gen-cpp2/service1.tcc"
#include "thrift/compiler/test/fixtures/fatal/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace test_cpp2 { namespace cpp_reflection {
std::unique_ptr<apache::thrift::AsyncProcessor> service1SvIf::getProcessor() {
  return std::make_unique<service1AsyncProcessor>(this);
}

service1SvIf::CreateMethodMetadataResult service1SvIf::createMethodMetadata() {
  return ::apache::thrift::detail::ap::createMethodMetadataMap<service1AsyncProcessor>();
}


void service1SvIf::method1() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method1");
}

folly::SemiFuture<folly::Unit> service1SvIf::semifuture_method1() {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  method1();
  return folly::makeSemiFuture();
}

folly::Future<folly::Unit> service1SvIf::future_method1() {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method1.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method1(), getInternalKeepAlive());
}

void service1SvIf::async_tm_method1(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method1.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method1.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method1();
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method1();
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        method1();
        callback->done();
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

void service1SvIf::method2(::std::int32_t /*x*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*y*/, double /*z*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method2");
}

folly::SemiFuture<folly::Unit> service1SvIf::semifuture_method2(::std::int32_t p_x, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_y, double p_z) {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method2.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  method2(p_x, std::move(p_y), p_z);
  return folly::makeSemiFuture();
}

folly::Future<folly::Unit> service1SvIf::future_method2(::std::int32_t p_x, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_y, double p_z) {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method2.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method2(p_x, std::move(p_y), p_z), getInternalKeepAlive());
}

void service1SvIf::async_tm_method2(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback, ::std::int32_t p_x, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_y, double p_z) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method2.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method2.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method2(p_x, std::move(p_y), p_z);
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method2(p_x, std::move(p_y), p_z);
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        method2(p_x, std::move(p_y), p_z);
        callback->done();
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

::std::int32_t service1SvIf::method3() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method3");
}

folly::SemiFuture<::std::int32_t> service1SvIf::semifuture_method3() {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method3.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  return method3();
}

folly::Future<::std::int32_t> service1SvIf::future_method3() {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method3.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method3(), getInternalKeepAlive());
}

void service1SvIf::async_tm_method3(std::unique_ptr<apache::thrift::HandlerCallback<::std::int32_t>> callback) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method3.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method3.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method3();
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method3();
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        callback->result(method3());
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

::std::int32_t service1SvIf::method4(::std::int32_t /*i*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*j*/, double /*k*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method4");
}

folly::SemiFuture<::std::int32_t> service1SvIf::semifuture_method4(::std::int32_t p_i, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_j, double p_k) {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method4.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  return method4(p_i, std::move(p_j), p_k);
}

folly::Future<::std::int32_t> service1SvIf::future_method4(::std::int32_t p_i, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_j, double p_k) {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method4.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method4(p_i, std::move(p_j), p_k), getInternalKeepAlive());
}

void service1SvIf::async_tm_method4(std::unique_ptr<apache::thrift::HandlerCallback<::std::int32_t>> callback, ::std::int32_t p_i, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_j, double p_k) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method4.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method4.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method4(p_i, std::move(p_j), p_k);
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method4(p_i, std::move(p_j), p_k);
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        callback->result(method4(p_i, std::move(p_j), p_k));
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

void service1SvIf::method5(::test_cpp2::cpp_reflection::struct2& /*_return*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method5");
}

folly::SemiFuture<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>> service1SvIf::semifuture_method5() {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method5.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  auto ret = std::make_unique<::test_cpp2::cpp_reflection::struct2>();
  method5(*ret);
  return folly::makeSemiFuture(std::move(ret));
}

folly::Future<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>> service1SvIf::future_method5() {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method5.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method5(), getInternalKeepAlive());
}

void service1SvIf::async_tm_method5(std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>>> callback) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method5.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method5.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method5();
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method5();
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        ::test_cpp2::cpp_reflection::struct2 _return;
        method5(_return);
        callback->result(_return);
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

void service1SvIf::method6(::test_cpp2::cpp_reflection::struct2& /*_return*/, ::std::int32_t /*l*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*m*/, double /*n*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("method6");
}

folly::SemiFuture<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>> service1SvIf::semifuture_method6(::std::int32_t p_l, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_m, double p_n) {
  auto expected{apache::thrift::detail::si::InvocationType::SemiFuture};
  __fbthrift_invocation_method6.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::Sync, std::memory_order_relaxed);
  auto ret = std::make_unique<::test_cpp2::cpp_reflection::struct2>();
  method6(*ret, p_l, std::move(p_m), p_n);
  return folly::makeSemiFuture(std::move(ret));
}

folly::Future<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>> service1SvIf::future_method6(::std::int32_t p_l, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_m, double p_n) {
  auto expected{apache::thrift::detail::si::InvocationType::Future};
  __fbthrift_invocation_method6.compare_exchange_strong(expected, apache::thrift::detail::si::InvocationType::SemiFuture, std::memory_order_relaxed);
  return apache::thrift::detail::si::future(semifuture_method6(p_l, std::move(p_m), p_n), getInternalKeepAlive());
}

void service1SvIf::async_tm_method6(std::unique_ptr<apache::thrift::HandlerCallback<std::unique_ptr<::test_cpp2::cpp_reflection::struct2>>> callback, ::std::int32_t p_l, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> p_m, double p_n) {
  // It's possible the coroutine versions will delegate to a future-based
  // version. If that happens, we need the RequestParams arguments to be
  // available to the future through the thread-local backchannel, so we create
  // a RAII object that sets up RequestParams and clears them on destruction.
  apache::thrift::detail::si::AsyncTmPrep asyncTmPrep(this, callback.get());
  auto invocationType = __fbthrift_invocation_method6.load(std::memory_order_relaxed);
  try {
    switch (invocationType) {
      case apache::thrift::detail::si::InvocationType::AsyncTm:
      {
        __fbthrift_invocation_method6.compare_exchange_strong(invocationType, apache::thrift::detail::si::InvocationType::Future, std::memory_order_relaxed);
        FOLLY_FALLTHROUGH;
      }
      case apache::thrift::detail::si::InvocationType::Future:
      {
        auto fut = future_method6(p_l, std::move(p_m), p_n);
        apache::thrift::detail::si::async_tm_future(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::SemiFuture:
      {
        auto fut = semifuture_method6(p_l, std::move(p_m), p_n);
        apache::thrift::detail::si::async_tm_semifuture(std::move(callback), std::move(fut));
        return;
      }
      case apache::thrift::detail::si::InvocationType::Sync:
      {
        ::test_cpp2::cpp_reflection::struct2 _return;
        method6(_return, p_l, std::move(p_m), p_n);
        callback->result(_return);
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

void service1SvNull::method1() {
  return;
}

void service1SvNull::method2(::std::int32_t /*x*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*y*/, double /*z*/) {
  return;
}

::std::int32_t service1SvNull::method3() {
  return 0;
}

::std::int32_t service1SvNull::method4(::std::int32_t /*i*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*j*/, double /*k*/) {
  return 0;
}

void service1SvNull::method5(::test_cpp2::cpp_reflection::struct2& /*_return*/) {}

void service1SvNull::method6(::test_cpp2::cpp_reflection::struct2& /*_return*/, ::std::int32_t /*l*/, std::unique_ptr<::test_cpp2::cpp_reflection::struct1> /*m*/, double /*n*/) {}



const char* service1AsyncProcessor::getServiceName() {
  return "service1";
}

void service1AsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<service1SvIf>::gen(response);
}

void service1AsyncProcessor::processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

void service1AsyncProcessor::processSerializedCompressedRequestWithMetadata(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), methodMetadata, protType, context, eb, tm);
}

const service1AsyncProcessor::ProcessMap& service1AsyncProcessor::getOwnProcessMap() {
  return kOwnProcessMap_;
}

const service1AsyncProcessor::ProcessMap service1AsyncProcessor::kOwnProcessMap_ {
  {"method1", {&service1AsyncProcessor::setUpAndProcess_method1<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method1<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"method2", {&service1AsyncProcessor::setUpAndProcess_method2<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method2<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"method3", {&service1AsyncProcessor::setUpAndProcess_method3<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method3<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"method4", {&service1AsyncProcessor::setUpAndProcess_method4<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method4<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"method5", {&service1AsyncProcessor::setUpAndProcess_method5<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method5<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
  {"method6", {&service1AsyncProcessor::setUpAndProcess_method6<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>, &service1AsyncProcessor::setUpAndProcess_method6<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>}},
};

}} // test_cpp2::cpp_reflection
