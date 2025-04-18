/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include <thrift/lib/cpp2/gen/service_h.h>

#include "thrift/compiler/test/fixtures/py3/gen-cpp2/DerivedServiceAsyncClient.h"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/py3/gen-cpp2/SimpleService.h"

namespace folly {
  class IOBuf;
  class IOBufQueue;
}
namespace apache { namespace thrift {
  class Cpp2RequestContext;
  class BinaryProtocolReader;
  class CompactProtocolReader;
  namespace transport { class THeader; }
}}

namespace py3 { namespace simple {

class DerivedServiceSvAsyncIf {
 public:
  virtual ~DerivedServiceSvAsyncIf() {}
  virtual void async_tm_get_six(std::unique_ptr<apache::thrift::HandlerCallback<::std::int32_t>> callback) = 0;
  virtual folly::Future<::std::int32_t> future_get_six() = 0;
  virtual folly::SemiFuture<::std::int32_t> semifuture_get_six() = 0;
};

class DerivedServiceAsyncProcessor;

class DerivedServiceSvIf : public DerivedServiceSvAsyncIf, virtual public ::py3::simple::SimpleServiceSvIf {
 public:
  typedef DerivedServiceAsyncProcessor ProcessorType;
  std::unique_ptr<apache::thrift::AsyncProcessor> getProcessor() override;
  CreateMethodMetadataResult createMethodMetadata() override;


  virtual ::std::int32_t get_six();
  folly::Future<::std::int32_t> future_get_six() override;
  folly::SemiFuture<::std::int32_t> semifuture_get_six() override;
  void async_tm_get_six(std::unique_ptr<apache::thrift::HandlerCallback<::std::int32_t>> callback) override;
 private:
  std::atomic<apache::thrift::detail::si::InvocationType> __fbthrift_invocation_get_six{apache::thrift::detail::si::InvocationType::AsyncTm};
};

class DerivedServiceSvNull : public DerivedServiceSvIf, virtual public ::py3::simple::SimpleServiceSvIf {
 public:
  ::std::int32_t get_six() override;
};

class DerivedServiceAsyncProcessor : public ::py3::simple::SimpleServiceAsyncProcessor {
 public:
  const char* getServiceName() override;
  void getServiceMetadata(apache::thrift::metadata::ThriftServiceMetadataResponse& response) override;
  using BaseAsyncProcessor = ::py3::simple::SimpleServiceAsyncProcessor;
 protected:
  DerivedServiceSvIf* iface_;
 public:
  // This is implemented in case the corresponding AsyncProcessorFactory did not implement createMethodMetadata.
  // This can happen if the service is using a custom AsyncProcessorFactory but re-using the same AsyncProcessor.
  void processSerializedCompressedRequest(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) override;
  // By default, this overload will be called for generated services
  void processSerializedCompressedRequestWithMetadata(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, const apache::thrift::AsyncProcessorFactory::MethodMetadata& methodMetadata, apache::thrift::protocol::PROTOCOL_TYPES protType, apache::thrift::Cpp2RequestContext* context, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm) override;
 public:
  using ProcessFuncs = GeneratedAsyncProcessor::ProcessFuncs<DerivedServiceAsyncProcessor>;
  using ProcessMap = GeneratedAsyncProcessor::ProcessMap<ProcessFuncs>;
  static const DerivedServiceAsyncProcessor::ProcessMap& getOwnProcessMap();
 private:
  static const DerivedServiceAsyncProcessor::ProcessMap kOwnProcessMap_;
 private:
  template <typename ProtocolIn_, typename ProtocolOut_>
  void setUpAndProcess_get_six(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx, folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <typename ProtocolIn_, typename ProtocolOut_>
  void process_get_six(apache::thrift::ResponseChannelRequest::UniquePtr req, apache::thrift::SerializedCompressedRequest&& serializedRequest, apache::thrift::Cpp2RequestContext* ctx,folly::EventBase* eb, apache::thrift::concurrency::ThreadManager* tm);
  template <class ProtocolIn_, class ProtocolOut_>
  static apache::thrift::LegacySerializedResponse return_get_six(int32_t protoSeqId, apache::thrift::ContextStack* ctx, ::std::int32_t const& _return);
  template <class ProtocolIn_, class ProtocolOut_>
  static void throw_wrapped_get_six(apache::thrift::ResponseChannelRequest::UniquePtr req,int32_t protoSeqId,apache::thrift::ContextStack* ctx,folly::exception_wrapper ew,apache::thrift::Cpp2RequestContext* reqCtx);
 public:
  DerivedServiceAsyncProcessor(DerivedServiceSvIf* iface) :
      ::py3::simple::SimpleServiceAsyncProcessor(iface),
      iface_(iface) {}

  virtual ~DerivedServiceAsyncProcessor() {}
};

}} // py3::simple
