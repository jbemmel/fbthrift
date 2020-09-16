/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "thrift/compiler/test/fixtures/mcpp2-compare/gen-cpp2/ExtraService.h"
#include "thrift/compiler/test/fixtures/mcpp2-compare/gen-cpp2/ExtraService.tcc"
#include "thrift/compiler/test/fixtures/mcpp2-compare/gen-cpp2/extra_services_metadata.h"
#include <thrift/lib/cpp2/gen/service_cpp.h>

namespace extra { namespace svc {
std::unique_ptr<apache::thrift::AsyncProcessor> ExtraServiceSvIf::getProcessor() {
  return std::make_unique<ExtraServiceAsyncProcessor>(this);
}


bool ExtraServiceSvIf::simple_function() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("simple_function");
}

folly::SemiFuture<bool> ExtraServiceSvIf::semifuture_simple_function() {
  return apache::thrift::detail::si::semifuture([&] {
    return simple_function();
  });
}

folly::Future<bool> ExtraServiceSvIf::future_simple_function() {
  return apache::thrift::detail::si::future(semifuture_simple_function(), getThreadManager());
}

void ExtraServiceSvIf::async_tm_simple_function(std::unique_ptr<apache::thrift::HandlerCallback<bool>> callback) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_simple_function();
  });
}

void ExtraServiceSvIf::async_eb_throws_function(std::unique_ptr<apache::thrift::HandlerCallback<void>> callback) {
  callback->exception(apache::thrift::TApplicationException("Function throws_function is unimplemented"));
}

bool ExtraServiceSvIf::throws_function2(bool /*param1*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("throws_function2");
}

folly::SemiFuture<bool> ExtraServiceSvIf::semifuture_throws_function2(bool param1) {
  return apache::thrift::detail::si::semifuture([&] {
    return throws_function2(param1);
  });
}

folly::Future<bool> ExtraServiceSvIf::future_throws_function2(bool param1) {
  return apache::thrift::detail::si::future(semifuture_throws_function2(param1), getThreadManager());
}

void ExtraServiceSvIf::async_tm_throws_function2(std::unique_ptr<apache::thrift::HandlerCallback<bool>> callback, bool param1) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_throws_function2(param1);
  });
}

void ExtraServiceSvIf::throws_function3(::std::map<int32_t, ::std::string>& /*_return*/, bool /*param1*/, const ::std::string& /*param2*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("throws_function3");
}

folly::SemiFuture<::std::map<int32_t, ::std::string>> ExtraServiceSvIf::semifuture_throws_function3(bool param1, const ::std::string& param2) {
  return apache::thrift::detail::si::semifuture_returning([&](::std::map<int32_t, ::std::string>& _return) { throws_function3(_return, param1, param2); });
}

folly::Future<::std::map<int32_t, ::std::string>> ExtraServiceSvIf::future_throws_function3(bool param1, const ::std::string& param2) {
  return apache::thrift::detail::si::future(semifuture_throws_function3(param1, param2), getThreadManager());
}

void ExtraServiceSvIf::async_tm_throws_function3(std::unique_ptr<apache::thrift::HandlerCallback<::std::map<int32_t, ::std::string>>> callback, bool param1, const ::std::string& param2) {
  apache::thrift::detail::si::async_tm(this, std::move(callback), [&] {
    return future_throws_function3(param1, param2);
  });
}

void ExtraServiceSvIf::oneway_void_ret() {
  apache::thrift::detail::si::throw_app_exn_unimplemented("oneway_void_ret");
}

folly::SemiFuture<folly::Unit> ExtraServiceSvIf::semifuture_oneway_void_ret() {
  return apache::thrift::detail::si::semifuture([&] {
    return oneway_void_ret();
  });
}

folly::Future<folly::Unit> ExtraServiceSvIf::future_oneway_void_ret() {
  return apache::thrift::detail::si::future(semifuture_oneway_void_ret(), getThreadManager());
}

void ExtraServiceSvIf::async_tm_oneway_void_ret(std::unique_ptr<apache::thrift::HandlerCallbackBase> callback) {
  apache::thrift::detail::si::async_tm_oneway(this, std::move(callback), [&] {
    return future_oneway_void_ret();
  });
}

void ExtraServiceSvIf::oneway_void_ret_i32_i32_i32_i32_i32_param(int32_t /*param1*/, int32_t /*param2*/, int32_t /*param3*/, int32_t /*param4*/, int32_t /*param5*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("oneway_void_ret_i32_i32_i32_i32_i32_param");
}

folly::SemiFuture<folly::Unit> ExtraServiceSvIf::semifuture_oneway_void_ret_i32_i32_i32_i32_i32_param(int32_t param1, int32_t param2, int32_t param3, int32_t param4, int32_t param5) {
  return apache::thrift::detail::si::semifuture([&] {
    return oneway_void_ret_i32_i32_i32_i32_i32_param(param1, param2, param3, param4, param5);
  });
}

folly::Future<folly::Unit> ExtraServiceSvIf::future_oneway_void_ret_i32_i32_i32_i32_i32_param(int32_t param1, int32_t param2, int32_t param3, int32_t param4, int32_t param5) {
  return apache::thrift::detail::si::future(semifuture_oneway_void_ret_i32_i32_i32_i32_i32_param(param1, param2, param3, param4, param5), getThreadManager());
}

void ExtraServiceSvIf::async_tm_oneway_void_ret_i32_i32_i32_i32_i32_param(std::unique_ptr<apache::thrift::HandlerCallbackBase> callback, int32_t param1, int32_t param2, int32_t param3, int32_t param4, int32_t param5) {
  apache::thrift::detail::si::async_tm_oneway(this, std::move(callback), [&] {
    return future_oneway_void_ret_i32_i32_i32_i32_i32_param(param1, param2, param3, param4, param5);
  });
}

void ExtraServiceSvIf::async_eb_oneway_void_ret_map_setlist_param(std::unique_ptr<apache::thrift::HandlerCallbackBase> /*callback*/, const ::std::map<::std::string, int64_t>& /*param1*/, const ::std::set<::std::vector<::std::string>>& /*param2*/) {
  LOG(DFATAL) << "Function oneway_void_ret_map_setlist_param is unimplemented";
}

void ExtraServiceSvIf::oneway_void_ret_struct_param(const  ::some::valid::ns::MyStruct& /*param1*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("oneway_void_ret_struct_param");
}

folly::SemiFuture<folly::Unit> ExtraServiceSvIf::semifuture_oneway_void_ret_struct_param(const  ::some::valid::ns::MyStruct& param1) {
  return apache::thrift::detail::si::semifuture([&] {
    return oneway_void_ret_struct_param(param1);
  });
}

folly::Future<folly::Unit> ExtraServiceSvIf::future_oneway_void_ret_struct_param(const  ::some::valid::ns::MyStruct& param1) {
  return apache::thrift::detail::si::future(semifuture_oneway_void_ret_struct_param(param1), getThreadManager());
}

void ExtraServiceSvIf::async_tm_oneway_void_ret_struct_param(std::unique_ptr<apache::thrift::HandlerCallbackBase> callback, const  ::some::valid::ns::MyStruct& param1) {
  apache::thrift::detail::si::async_tm_oneway(this, std::move(callback), [&] {
    return future_oneway_void_ret_struct_param(param1);
  });
}

void ExtraServiceSvIf::oneway_void_ret_listunion_param(const ::std::vector< ::some::valid::ns::ComplexUnion>& /*param1*/) {
  apache::thrift::detail::si::throw_app_exn_unimplemented("oneway_void_ret_listunion_param");
}

folly::SemiFuture<folly::Unit> ExtraServiceSvIf::semifuture_oneway_void_ret_listunion_param(const ::std::vector< ::some::valid::ns::ComplexUnion>& param1) {
  return apache::thrift::detail::si::semifuture([&] {
    return oneway_void_ret_listunion_param(param1);
  });
}

folly::Future<folly::Unit> ExtraServiceSvIf::future_oneway_void_ret_listunion_param(const ::std::vector< ::some::valid::ns::ComplexUnion>& param1) {
  return apache::thrift::detail::si::future(semifuture_oneway_void_ret_listunion_param(param1), getThreadManager());
}

void ExtraServiceSvIf::async_tm_oneway_void_ret_listunion_param(std::unique_ptr<apache::thrift::HandlerCallbackBase> callback, const ::std::vector< ::some::valid::ns::ComplexUnion>& param1) {
  apache::thrift::detail::si::async_tm_oneway(this, std::move(callback), [&] {
    return future_oneway_void_ret_listunion_param(param1);
  });
}

bool ExtraServiceSvNull::simple_function() {
  return 0;
}

bool ExtraServiceSvNull::throws_function2(bool /*param1*/) {
  return 0;
}

void ExtraServiceSvNull::throws_function3(::std::map<int32_t, ::std::string>& /*_return*/, bool /*param1*/, const ::std::string& /*param2*/) {}

void ExtraServiceSvNull::oneway_void_ret() {
  return;
}

void ExtraServiceSvNull::oneway_void_ret_i32_i32_i32_i32_i32_param(int32_t /*param1*/, int32_t /*param2*/, int32_t /*param3*/, int32_t /*param4*/, int32_t /*param5*/) {
  return;
}

void ExtraServiceSvNull::oneway_void_ret_struct_param(const  ::some::valid::ns::MyStruct& /*param1*/) {
  return;
}

void ExtraServiceSvNull::oneway_void_ret_listunion_param(const ::std::vector< ::some::valid::ns::ComplexUnion>& /*param1*/) {
  return;
}



const char* ExtraServiceAsyncProcessor::getServiceName() {
  return "ExtraService";
}

void ExtraServiceAsyncProcessor::getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) {
  ::apache::thrift::detail::md::ServiceMetadata<ExtraServiceSvIf>::gen(*response.metadata_ref(), *response.context_ref());
}

void ExtraServiceAsyncProcessor::processSerializedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) {
  apache::thrift::detail::ap::process(this, std::move(req), std::move(serializedRequest), protType, context, eb, tm);
}

std::shared_ptr<folly::RequestContext> ExtraServiceAsyncProcessor::getBaseContextForRequest() {
  return iface_->getBaseContextForRequest();
}

const ExtraServiceAsyncProcessor::ProcessMap& ExtraServiceAsyncProcessor::getBinaryProtocolProcessMap() {
  return binaryProcessMap_;
}

const ExtraServiceAsyncProcessor::ProcessMap ExtraServiceAsyncProcessor::binaryProcessMap_ {
  {"simple_function", &ExtraServiceAsyncProcessor::_processInThread_simple_function<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"throws_function", &ExtraServiceAsyncProcessor::process_throws_function<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"throws_function2", &ExtraServiceAsyncProcessor::_processInThread_throws_function2<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"throws_function3", &ExtraServiceAsyncProcessor::_processInThread_throws_function3<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"oneway_void_ret", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"oneway_void_ret_i32_i32_i32_i32_i32_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_i32_i32_i32_i32_i32_param<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"oneway_void_ret_map_setlist_param", &ExtraServiceAsyncProcessor::process_oneway_void_ret_map_setlist_param<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"oneway_void_ret_struct_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_struct_param<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
  {"oneway_void_ret_listunion_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_listunion_param<apache::thrift::BinaryProtocolReader, apache::thrift::BinaryProtocolWriter>},
};

const ExtraServiceAsyncProcessor::ProcessMap& ExtraServiceAsyncProcessor::getCompactProtocolProcessMap() {
  return compactProcessMap_;
}

const ExtraServiceAsyncProcessor::ProcessMap ExtraServiceAsyncProcessor::compactProcessMap_ {
  {"simple_function", &ExtraServiceAsyncProcessor::_processInThread_simple_function<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"throws_function", &ExtraServiceAsyncProcessor::process_throws_function<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"throws_function2", &ExtraServiceAsyncProcessor::_processInThread_throws_function2<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"throws_function3", &ExtraServiceAsyncProcessor::_processInThread_throws_function3<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"oneway_void_ret", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"oneway_void_ret_i32_i32_i32_i32_i32_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_i32_i32_i32_i32_i32_param<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"oneway_void_ret_map_setlist_param", &ExtraServiceAsyncProcessor::process_oneway_void_ret_map_setlist_param<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"oneway_void_ret_struct_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_struct_param<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
  {"oneway_void_ret_listunion_param", &ExtraServiceAsyncProcessor::_processInThread_oneway_void_ret_listunion_param<apache::thrift::CompactProtocolReader, apache::thrift::CompactProtocolWriter>},
};

}} // extra::svc
