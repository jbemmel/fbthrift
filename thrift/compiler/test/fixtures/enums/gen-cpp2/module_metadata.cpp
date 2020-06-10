/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include <thrift/lib/cpp2/gen/module_metadata_cpp.h>
#include "thrift/compiler/test/fixtures/enums/gen-cpp2/module_metadata.h"

namespace apache {
namespace thrift {
namespace detail {
namespace md {
using ThriftMetadata = ::apache::thrift::metadata::ThriftMetadata;
using ThriftPrimitiveType = ::apache::thrift::metadata::ThriftPrimitiveType;
using ThriftType = ::apache::thrift::metadata::ThriftType;
using ThriftService = ::apache::thrift::metadata::ThriftService;
using ThriftServiceContext = ::apache::thrift::metadata::ThriftServiceContext;
using ThriftFunctionGenerator = void (*)(ThriftMetadata&, ThriftService&);

void EnumMetadata<::cpp2::Metasyntactic>::gen(ThriftMetadata& metadata) {
  auto res = metadata.enums.emplace("module.Metasyntactic", ::apache::thrift::metadata::ThriftEnum{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftEnum& enum_metadata = res.first->second;
  enum_metadata.name = "module.Metasyntactic";
  using EnumTraits = TEnumTraits<::cpp2::Metasyntactic>;
  for (std::size_t i = 0; i < EnumTraits::size; ++i) {
    enum_metadata.elements.emplace(static_cast<int32_t>(EnumTraits::values[i]), EnumTraits::names[i].str());
  }
}

void StructMetadata<::cpp2::SomeStruct>::gen(ThriftMetadata& metadata) {
  auto res = metadata.structs.emplace("module.SomeStruct", ::apache::thrift::metadata::ThriftStruct{});
  if (!res.second) {
    return;
  }
  ::apache::thrift::metadata::ThriftStruct& module_SomeStruct = res.first->second;
  module_SomeStruct.name = "module.SomeStruct";
  module_SomeStruct.is_union = false;
  static const std::tuple<int32_t, const char*, bool, std::unique_ptr<MetadataTypeInterface>>
  module_SomeStruct_fields[] = {
    std::make_tuple(1, "reasonable", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic")),
    std::make_tuple(2, "fine", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic")),
    std::make_tuple(3, "questionable", false, std::make_unique<Enum< ::cpp2::Metasyntactic>>("module.Metasyntactic")),
    std::make_tuple(4, "tags", false, std::make_unique<Set>(std::make_unique<Primitive>(ThriftPrimitiveType::THRIFT_I32_TYPE))),
  };
  for (const auto& f : module_SomeStruct_fields) {
    ::apache::thrift::metadata::ThriftField field;
    field.id = std::get<0>(f);
    field.name = std::get<1>(f);
    field.is_optional = std::get<2>(f);
    std::get<3>(f)->writeAndGenType(field.type, metadata);
    module_SomeStruct.fields.push_back(std::move(field));
  }
}

} // namespace md
} // namespace detail
} // namespace thrift
} // namespace apache