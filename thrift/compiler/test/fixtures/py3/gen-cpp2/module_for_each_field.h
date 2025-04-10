/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include "thrift/compiler/test/fixtures/py3/gen-cpp2/module_metadata.h"
#include <thrift/lib/cpp2/visitation/for_each.h>

namespace apache {
namespace thrift {
namespace detail {

template <>
struct ForEachField<::py3::simple::SimpleException> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).err_code_ref()...);
  }
};

template <>
struct ForEachField<::py3::simple::OptionalRefStruct> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).optional_blob_ref()...);
  }
};

template <>
struct ForEachField<::py3::simple::SimpleStruct> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).is_on_ref()...);
    f(1, static_cast<T&&>(t).tiny_int_ref()...);
    f(2, static_cast<T&&>(t).small_int_ref()...);
    f(3, static_cast<T&&>(t).nice_sized_int_ref()...);
    f(4, static_cast<T&&>(t).big_int_ref()...);
    f(5, static_cast<T&&>(t).real_ref()...);
    f(6, static_cast<T&&>(t).smaller_real_ref()...);
    f(7, static_cast<T&&>(t).hidden_field_ref()...);
  }
};

template <>
struct ForEachField<::py3::simple::ComplexStruct> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).structOne_ref()...);
    f(1, static_cast<T&&>(t).structTwo_ref()...);
    f(2, static_cast<T&&>(t).an_integer_ref()...);
    f(3, static_cast<T&&>(t).name_ref()...);
    f(4, static_cast<T&&>(t).an_enum_ref()...);
    f(5, static_cast<T&&>(t).some_bytes_ref()...);
    f(6, static_cast<T&&>(t).from_ref()...);
    f(7, static_cast<T&&>(t).cdef_ref()...);
    f(8, static_cast<T&&>(t).bytes_with_cpp_type_ref()...);
  }
};

template <>
struct ForEachField<::py3::simple::BinaryUnion> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).iobuf_val_ref()...);
  }
};

template <>
struct ForEachField<::py3::simple::BinaryUnionStruct> {
  template <typename F, typename... T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, FOLLY_MAYBE_UNUSED T&&... t) const {
    f(0, static_cast<T&&>(t).u_ref()...);
  }
};
} // namespace detail
} // namespace thrift
} // namespace apache
