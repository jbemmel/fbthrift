/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_types_h.h>


#include "other/gen-cpp2/matching_module_name_types.h"

namespace apache {
namespace thrift {
namespace accessor {
#ifndef APACHE_THRIFT_ACCESSOR_OtherStructField
#define APACHE_THRIFT_ACCESSOR_OtherStructField
APACHE_THRIFT_DEFINE_ACCESSOR(OtherStructField);
#endif
} // namespace accessor
} // namespace thrift
} // namespace apache

// BEGIN declare_enums

// END declare_enums
// BEGIN struct_indirection

// END struct_indirection
// BEGIN forward_declare
namespace matching_module_name {
class MyStruct;
} // matching_module_name
// END forward_declare
// BEGIN typedefs

// END typedefs
// BEGIN hash_and_equal_to
// END hash_and_equal_to
namespace matching_module_name {
class MyStruct final : private apache::thrift::detail::st::ComparisonOperators<MyStruct> {
 public:

  MyStruct() {}
  // FragileConstructor for use in initialization lists only.
  [[deprecated("This constructor is deprecated")]]
  MyStruct(apache::thrift::FragileConstructor,  ::matching_module_name::OtherStruct OtherStructField__arg);

  MyStruct(MyStruct&&) = default;

  MyStruct(const MyStruct&) = default;

  MyStruct& operator=(MyStruct&&) = default;

  MyStruct& operator=(const MyStruct&) = default;
  void __clear();
 public:
   ::matching_module_name::OtherStruct OtherStructField;

 public:
  struct __isset {
    bool OtherStructField;
  } __isset = {};
  bool operator==(const MyStruct& rhs) const;
  bool operator<(const MyStruct& rhs) const;
  const  ::matching_module_name::OtherStruct& get_OtherStructField() const&;
   ::matching_module_name::OtherStruct get_OtherStructField() &&;

  template <typename T_MyStruct_OtherStructField_struct_setter =  ::matching_module_name::OtherStruct>
   ::matching_module_name::OtherStruct& set_OtherStructField(T_MyStruct_OtherStructField_struct_setter&& OtherStructField_) {
    OtherStructField = std::forward<T_MyStruct_OtherStructField_struct_setter>(OtherStructField_);
    __isset.OtherStructField = true;
    return OtherStructField;
  }

  template <class Protocol_>
  uint32_t read(Protocol_* iprot);
  template <class Protocol_>
  uint32_t serializedSize(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t serializedSizeZC(Protocol_ const* prot_) const;
  template <class Protocol_>
  uint32_t write(Protocol_* prot_) const;

 private:
  template <class Protocol_>
  void readNoXfer(Protocol_* iprot);

  friend class ::apache::thrift::Cpp2Ops< MyStruct >;
};

void swap(MyStruct& a, MyStruct& b);

template <class Protocol_>
uint32_t MyStruct::read(Protocol_* iprot) {
  auto _xferStart = iprot->getCursorPosition();
  readNoXfer(iprot);
  return iprot->getCursorPosition() - _xferStart;
}

} // matching_module_name
