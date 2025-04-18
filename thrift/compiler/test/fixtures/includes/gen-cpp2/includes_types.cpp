/**
 * Autogenerated by Thrift for src/includes.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include "thrift/compiler/test/fixtures/includes/gen-cpp2/includes_types.h"
#include "thrift/compiler/test/fixtures/includes/gen-cpp2/includes_types.tcc"

#include <thrift/lib/cpp2/gen/module_types_cpp.h>

#include "thrift/compiler/test/fixtures/includes/gen-cpp2/includes_data.h"


namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::cpp2::Included>::translateFieldName(
    folly::StringPiece _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::cpp2::Included>;
  static const st::translate_field_name_table table{
      data::fields_size,
      data::fields_names.data(),
      data::fields_ids.data(),
      data::fields_types.data()};
  st::translate_field_name(_fname, fid, _ftype, table);
}

} // namespace detail
} // namespace thrift
} // namespace apache

namespace cpp2 {


THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Included::Included(apache::thrift::FragileConstructor, ::std::int64_t MyIntField__arg, ::cpp2::Foo MyTransitiveField__arg) :
    MyIntField(std::move(MyIntField__arg)),
    MyTransitiveField(std::move(MyTransitiveField__arg)) {
  __isset.MyIntField = true;
  __isset.MyTransitiveField = true;
}
THRIFT_IGNORE_ISSET_USE_WARNING_END

void Included::__clear() {
  // clear all fields
  this->MyIntField = 0LL;
  this->MyTransitiveField.__clear();
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  __isset = {};
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

bool Included::operator==(const Included& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.MyIntField_ref() == rhs.MyIntField_ref())) {
    return false;
  }
  if (!(lhs.MyTransitiveField_ref() == rhs.MyTransitiveField_ref())) {
    return false;
  }
  return true;
}

bool Included::operator<(const Included& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.MyIntField_ref() == rhs.MyIntField_ref())) {
    return lhs.MyIntField_ref() < rhs.MyIntField_ref();
  }
  if (!(lhs.MyTransitiveField_ref() == rhs.MyTransitiveField_ref())) {
    return lhs.MyTransitiveField_ref() < rhs.MyTransitiveField_ref();
  }
  return false;
}

const ::cpp2::Foo& Included::get_MyTransitiveField() const& {
  return MyTransitiveField;
}

::cpp2::Foo Included::get_MyTransitiveField() && {
  return std::move(MyTransitiveField);
}


void swap(Included& a, Included& b) {
  using ::std::swap;
  swap(a.MyIntField_ref().value(), b.MyIntField_ref().value());
  swap(a.MyTransitiveField_ref().value(), b.MyTransitiveField_ref().value());
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  swap(a.__isset, b.__isset);
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

template void Included::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
template uint32_t Included::write<>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Included::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
template uint32_t Included::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
template void Included::readNoXfer<>(apache::thrift::CompactProtocolReader*);
template uint32_t Included::write<>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Included::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
template uint32_t Included::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        Included,
        ::apache::thrift::type_class::structure,
        ::cpp2::Foo>,
    "inconsistent use of json option");

static_assert(
    ::apache::thrift::detail::st::gen_check_nimble<
        Included,
        ::apache::thrift::type_class::structure,
        ::cpp2::Foo>,
    "inconsistent use of nimble option");

} // cpp2
