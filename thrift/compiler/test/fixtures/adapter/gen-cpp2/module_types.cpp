/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#include "thrift/compiler/test/fixtures/adapter/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/adapter/gen-cpp2/module_types.tcc"

#include <thrift/lib/cpp2/gen/module_types_cpp.h>

#include "thrift/compiler/test/fixtures/adapter/gen-cpp2/module_data.h"


namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::cpp2::Foo>::translateFieldName(
    folly::StringPiece _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::cpp2::Foo>;
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
Foo::Foo(const Foo&) = default;
Foo& Foo::operator=(const Foo&) = default;
THRIFT_IGNORE_ISSET_USE_WARNING_END
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Foo::Foo() :
      intField(my::Adapter1::fromThrift(0)),
      optionalIntField(my::Adapter1::fromThrift(0)),
      intFieldWithDefault(my::Adapter1::fromThrift(13)) {
}

THRIFT_IGNORE_ISSET_USE_WARNING_END

Foo::~Foo() {}

THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Foo::Foo(Foo&& other) noexcept  :
    intField(std::move(other.intField)),
    optionalIntField(std::move(other.optionalIntField)),
    intFieldWithDefault(std::move(other.intFieldWithDefault)),
    setField(std::move(other.setField)),
    optionalSetField(std::move(other.optionalSetField)),
    mapField(std::move(other.mapField)),
    optionalMapField(std::move(other.optionalMapField)),
    binaryField(std::move(other.binaryField)),
    __isset(other.__isset) {}
Foo& Foo::operator=(FOLLY_MAYBE_UNUSED Foo&& other) noexcept {
    this->intField = std::move(other.intField);
    this->optionalIntField = std::move(other.optionalIntField);
    this->intFieldWithDefault = std::move(other.intFieldWithDefault);
    this->setField = std::move(other.setField);
    this->optionalSetField = std::move(other.optionalSetField);
    this->mapField = std::move(other.mapField);
    this->optionalMapField = std::move(other.optionalMapField);
    this->binaryField = std::move(other.binaryField);
    __isset = other.__isset;
    return *this;
}
THRIFT_IGNORE_ISSET_USE_WARNING_END


THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Foo::Foo(apache::thrift::FragileConstructor, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> optionalIntField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::int32_t> intFieldWithDefault__arg, ::cpp2::SetWithAdapter setField__arg, ::cpp2::SetWithAdapter optionalSetField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> mapField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> optionalMapField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::std::string> binaryField__arg) :
    intField(std::move(intField__arg)),
    optionalIntField(std::move(optionalIntField__arg)),
    intFieldWithDefault(std::move(intFieldWithDefault__arg)),
    setField(std::move(setField__arg)),
    optionalSetField(std::move(optionalSetField__arg)),
    mapField(std::move(mapField__arg)),
    optionalMapField(std::move(optionalMapField__arg)),
    binaryField(std::move(binaryField__arg)) {
  __isset.intField = true;
  __isset.optionalIntField = true;
  __isset.intFieldWithDefault = true;
  __isset.setField = true;
  __isset.optionalSetField = true;
  __isset.mapField = true;
  __isset.optionalMapField = true;
  __isset.binaryField = true;
}
THRIFT_IGNORE_ISSET_USE_WARNING_END

void Foo::__clear() {
  // clear all fields
  this->intField = {};
  this->optionalIntField = {};
  this->intFieldWithDefault = {};
  this->setField.clear();
  this->optionalSetField.clear();
  this->mapField.clear();
  this->optionalMapField.clear();
  this->binaryField = {};
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  __isset = {};
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

bool Foo::operator==(const Foo& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.intField_ref() == rhs.intField_ref())) {
    return false;
  }
  if (!(lhs.optionalIntField_ref() == rhs.optionalIntField_ref())) {
    return false;
  }
  if (!(lhs.intFieldWithDefault_ref() == rhs.intFieldWithDefault_ref())) {
    return false;
  }
  if (!(lhs.setField_ref() == rhs.setField_ref())) {
    return false;
  }
  if (!(lhs.optionalSetField_ref() == rhs.optionalSetField_ref())) {
    return false;
  }
  if (!(lhs.mapField_ref() == rhs.mapField_ref())) {
    return false;
  }
  if (!(lhs.optionalMapField_ref() == rhs.optionalMapField_ref())) {
    return false;
  }
  if (!(lhs.binaryField_ref() == rhs.binaryField_ref())) {
    return false;
  }
  return true;
}

bool Foo::operator<(const Foo& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.intField_ref() == rhs.intField_ref())) {
    return lhs.intField_ref() < rhs.intField_ref();
  }
  if (!(lhs.optionalIntField_ref() == rhs.optionalIntField_ref())) {
    return lhs.optionalIntField_ref() < rhs.optionalIntField_ref();
  }
  if (!(lhs.intFieldWithDefault_ref() == rhs.intFieldWithDefault_ref())) {
    return lhs.intFieldWithDefault_ref() < rhs.intFieldWithDefault_ref();
  }
  if (!(lhs.setField_ref() == rhs.setField_ref())) {
    return lhs.setField_ref() < rhs.setField_ref();
  }
  if (!(lhs.optionalSetField_ref() == rhs.optionalSetField_ref())) {
    return lhs.optionalSetField_ref() < rhs.optionalSetField_ref();
  }
  if (!(lhs.mapField_ref() == rhs.mapField_ref())) {
    return lhs.mapField_ref() < rhs.mapField_ref();
  }
  if (!(lhs.optionalMapField_ref() == rhs.optionalMapField_ref())) {
    return lhs.optionalMapField_ref() < rhs.optionalMapField_ref();
  }
  if (!(lhs.binaryField_ref() == rhs.binaryField_ref())) {
    return lhs.binaryField_ref() < rhs.binaryField_ref();
  }
  return false;
}

const ::cpp2::SetWithAdapter& Foo::get_setField() const& {
  return setField;
}

::cpp2::SetWithAdapter Foo::get_setField() && {
  return std::move(setField);
}

const ::cpp2::SetWithAdapter* Foo::get_optionalSetField() const& {
  return optionalSetField_ref().has_value() ? std::addressof(optionalSetField) : nullptr;
}

::cpp2::SetWithAdapter* Foo::get_optionalSetField() & {
  return optionalSetField_ref().has_value() ? std::addressof(optionalSetField) : nullptr;
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>& Foo::get_mapField() const& {
  return mapField;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>> Foo::get_mapField() && {
  return std::move(mapField);
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>* Foo::get_optionalMapField() const& {
  return optionalMapField_ref().has_value() ? std::addressof(optionalMapField) : nullptr;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter3, ::std::map<::std::string, ::apache::thrift::adapt_detail::adapted_t<my::Adapter2, ::cpp2::ListWithElemAdapter>>>* Foo::get_optionalMapField() & {
  return optionalMapField_ref().has_value() ? std::addressof(optionalMapField) : nullptr;
}


void swap(Foo& a, Foo& b) {
  using ::std::swap;
  swap(a.intField_ref().value(), b.intField_ref().value());
  swap(a.optionalIntField_ref().value_unchecked(), b.optionalIntField_ref().value_unchecked());
  swap(a.intFieldWithDefault_ref().value(), b.intFieldWithDefault_ref().value());
  swap(a.setField_ref().value(), b.setField_ref().value());
  swap(a.optionalSetField_ref().value_unchecked(), b.optionalSetField_ref().value_unchecked());
  swap(a.mapField_ref().value(), b.mapField_ref().value());
  swap(a.optionalMapField_ref().value_unchecked(), b.optionalMapField_ref().value_unchecked());
  swap(a.binaryField_ref().value(), b.binaryField_ref().value());
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  swap(a.__isset, b.__isset);
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

template void Foo::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
template uint32_t Foo::write<>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Foo::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
template uint32_t Foo::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
template void Foo::readNoXfer<>(apache::thrift::CompactProtocolReader*);
template uint32_t Foo::write<>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Foo::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
template uint32_t Foo::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;



} // cpp2

namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::cpp2::Baz>::translateFieldName(
    folly::StringPiece _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::cpp2::Baz>;
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

namespace apache { namespace thrift {

constexpr std::size_t const TEnumTraits<::cpp2::Baz::Type>::size;
folly::Range<::cpp2::Baz::Type const*> const TEnumTraits<::cpp2::Baz::Type>::values = folly::range(TEnumDataStorage<::cpp2::Baz::Type>::values);
folly::Range<folly::StringPiece const*> const TEnumTraits<::cpp2::Baz::Type>::names = folly::range(TEnumDataStorage<::cpp2::Baz::Type>::names);

char const* TEnumTraits<::cpp2::Baz::Type>::findName(type value) {
  using factory = detail::TEnumMapFactory<::cpp2::Baz::Type>;
  static folly::Indestructible<factory::ValuesToNamesMapType> const map{
      factory::makeValuesToNamesMap()};
  auto found = map->find(value);
  return found == map->end() ? nullptr : found->second;
}

bool TEnumTraits<::cpp2::Baz::Type>::findValue(char const* name, type* out) {
  using factory = detail::TEnumMapFactory<::cpp2::Baz::Type>;
  static folly::Indestructible<factory::NamesToValuesMapType> const map{
      factory::makeNamesToValuesMap()};
  auto found = map->find(name);
  return found == map->end() ? false : (*out = found->second, true);
}
}} // apache::thrift
namespace cpp2 {

void Baz::__clear() {
  // clear all fields
  if (type_ == Type::__EMPTY__) { return; }
  switch(type_) {
    case Type::intField:
      destruct(value_.intField);
      break;
    case Type::setField:
      destruct(value_.setField);
      break;
    case Type::mapField:
      destruct(value_.mapField);
      break;
    case Type::binaryField:
      destruct(value_.binaryField);
      break;
    default:
      assert(false);
      break;
  }
  type_ = Type::__EMPTY__;
}

bool Baz::operator==(const Baz& rhs) const {
  if (type_ != rhs.type_) { return false; }
  switch(type_) {
    case Type::intField:
      return value_.intField == rhs.value_.intField;
    case Type::setField:
      return value_.setField == rhs.value_.setField;
    case Type::mapField:
      return value_.mapField == rhs.value_.mapField;
    case Type::binaryField:
      return value_.binaryField == rhs.value_.binaryField;
    default:
      return true;
  }
}

bool Baz::operator<(const Baz& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (lhs.type_ != rhs.type_) {
    return lhs.type_ < rhs.type_;
  }
  switch (lhs.type_) {
    case Type::intField:
      return lhs.value_.intField < rhs.value_.intField;
    case Type::setField:
      return lhs.value_.setField < rhs.value_.setField;
    case Type::mapField:
      return lhs.value_.mapField < rhs.value_.mapField;
    case Type::binaryField:
      return lhs.value_.binaryField < rhs.value_.binaryField;
    default:
      return false;
  }
}

void swap(Baz& a, Baz& b) {
  Baz temp(std::move(a));
  a = std::move(b);
  b = std::move(temp);
}

template void Baz::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
template uint32_t Baz::write<>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Baz::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
template uint32_t Baz::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
template void Baz::readNoXfer<>(apache::thrift::CompactProtocolReader*);
template uint32_t Baz::write<>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Baz::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
template uint32_t Baz::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;



} // cpp2

namespace apache {
namespace thrift {
namespace detail {

void TccStructTraits<::cpp2::Bar>::translateFieldName(
    folly::StringPiece _fname,
    int16_t& fid,
    apache::thrift::protocol::TType& _ftype) noexcept {
  using data = apache::thrift::TStructDataStorage<::cpp2::Bar>;
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
Bar::Bar(const Bar&) = default;
Bar& Bar::operator=(const Bar&) = default;
THRIFT_IGNORE_ISSET_USE_WARNING_END
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Bar::Bar() {
}

THRIFT_IGNORE_ISSET_USE_WARNING_END

Bar::~Bar() {}

THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Bar::Bar(Bar&& other) noexcept  :
    structField(std::move(other.structField)),
    optionalStructField(std::move(other.optionalStructField)),
    structListField(std::move(other.structListField)),
    optionalStructListField(std::move(other.optionalStructListField)),
    unionField(std::move(other.unionField)),
    optionalUnionField(std::move(other.optionalUnionField)),
    __isset(other.__isset) {}
Bar& Bar::operator=(FOLLY_MAYBE_UNUSED Bar&& other) noexcept {
    this->structField = std::move(other.structField);
    this->optionalStructField = std::move(other.optionalStructField);
    this->structListField = std::move(other.structListField);
    this->optionalStructListField = std::move(other.optionalStructListField);
    this->unionField = std::move(other.unionField);
    this->optionalUnionField = std::move(other.optionalUnionField);
    __isset = other.__isset;
    return *this;
}
THRIFT_IGNORE_ISSET_USE_WARNING_END


THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
Bar::Bar(apache::thrift::FragileConstructor, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> structField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> optionalStructField__arg, ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> structListField__arg, ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> optionalStructListField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz> unionField__arg, ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz> optionalUnionField__arg) :
    structField(std::move(structField__arg)),
    optionalStructField(std::move(optionalStructField__arg)),
    structListField(std::move(structListField__arg)),
    optionalStructListField(std::move(optionalStructListField__arg)),
    unionField(std::move(unionField__arg)),
    optionalUnionField(std::move(optionalUnionField__arg)) {
  __isset.structField = true;
  __isset.optionalStructField = true;
  __isset.structListField = true;
  __isset.optionalStructListField = true;
  __isset.unionField = true;
  __isset.optionalUnionField = true;
}
THRIFT_IGNORE_ISSET_USE_WARNING_END

void Bar::__clear() {
  // clear all fields
  this->structField.__clear();
  this->optionalStructField.__clear();
  this->structListField.clear();
  this->optionalStructListField.clear();
  this->unionField.__clear();
  this->optionalUnionField.__clear();
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  __isset = {};
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

bool Bar::operator==(const Bar& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.structField_ref() == rhs.structField_ref())) {
    return false;
  }
  if (!(lhs.optionalStructField_ref() == rhs.optionalStructField_ref())) {
    return false;
  }
  if (!(lhs.structListField_ref() == rhs.structListField_ref())) {
    return false;
  }
  if (!(lhs.optionalStructListField_ref() == rhs.optionalStructListField_ref())) {
    return false;
  }
  if (!(lhs.unionField_ref() == rhs.unionField_ref())) {
    return false;
  }
  if (!(lhs.optionalUnionField_ref() == rhs.optionalUnionField_ref())) {
    return false;
  }
  return true;
}

bool Bar::operator<(const Bar& rhs) const {
  (void)rhs;
  auto& lhs = *this;
  (void)lhs;
  if (!(lhs.structField_ref() == rhs.structField_ref())) {
    return lhs.structField_ref() < rhs.structField_ref();
  }
  if (!(lhs.optionalStructField_ref() == rhs.optionalStructField_ref())) {
    return lhs.optionalStructField_ref() < rhs.optionalStructField_ref();
  }
  if (!(lhs.structListField_ref() == rhs.structListField_ref())) {
    return lhs.structListField_ref() < rhs.structListField_ref();
  }
  if (!(lhs.optionalStructListField_ref() == rhs.optionalStructListField_ref())) {
    return lhs.optionalStructListField_ref() < rhs.optionalStructListField_ref();
  }
  if (!(lhs.unionField_ref() == rhs.unionField_ref())) {
    return lhs.unionField_ref() < rhs.unionField_ref();
  }
  if (!(lhs.optionalUnionField_ref() == rhs.optionalUnionField_ref())) {
    return lhs.optionalUnionField_ref() < rhs.optionalUnionField_ref();
  }
  return false;
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>& Bar::get_structField() const& {
  return structField;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo> Bar::get_structField() && {
  return std::move(structField);
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>* Bar::get_optionalStructField() const& {
  return optionalStructField_ref().has_value() ? std::addressof(optionalStructField) : nullptr;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>* Bar::get_optionalStructField() & {
  return optionalStructField_ref().has_value() ? std::addressof(optionalStructField) : nullptr;
}

const ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>& Bar::get_structListField() const& {
  return structListField;
}

::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>> Bar::get_structListField() && {
  return std::move(structListField);
}

const ::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>* Bar::get_optionalStructListField() const& {
  return optionalStructListField_ref().has_value() ? std::addressof(optionalStructListField) : nullptr;
}

::std::vector<::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>* Bar::get_optionalStructListField() & {
  return optionalStructListField_ref().has_value() ? std::addressof(optionalStructListField) : nullptr;
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>& Bar::get_unionField() const& {
  return unionField;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz> Bar::get_unionField() && {
  return std::move(unionField);
}

const ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>* Bar::get_optionalUnionField() const& {
  return optionalUnionField_ref().has_value() ? std::addressof(optionalUnionField) : nullptr;
}

::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>* Bar::get_optionalUnionField() & {
  return optionalUnionField_ref().has_value() ? std::addressof(optionalUnionField) : nullptr;
}


void swap(Bar& a, Bar& b) {
  using ::std::swap;
  swap(a.structField_ref().value(), b.structField_ref().value());
  swap(a.optionalStructField_ref().value_unchecked(), b.optionalStructField_ref().value_unchecked());
  swap(a.structListField_ref().value(), b.structListField_ref().value());
  swap(a.optionalStructListField_ref().value_unchecked(), b.optionalStructListField_ref().value_unchecked());
  swap(a.unionField_ref().value(), b.unionField_ref().value());
  swap(a.optionalUnionField_ref().value_unchecked(), b.optionalUnionField_ref().value_unchecked());
THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  swap(a.__isset, b.__isset);
THRIFT_IGNORE_ISSET_USE_WARNING_END
}

template void Bar::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
template uint32_t Bar::write<>(apache::thrift::BinaryProtocolWriter*) const;
template uint32_t Bar::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
template uint32_t Bar::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
template void Bar::readNoXfer<>(apache::thrift::CompactProtocolReader*);
template uint32_t Bar::write<>(apache::thrift::CompactProtocolWriter*) const;
template uint32_t Bar::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
template uint32_t Bar::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        Bar,
        ::apache::thrift::type_class::structure,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>,
    "inconsistent use of json option");
static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        Bar,
        ::apache::thrift::type_class::structure,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>,
    "inconsistent use of json option");
static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        Bar,
        ::apache::thrift::type_class::variant,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>>,
    "inconsistent use of json option");
static_assert(
    ::apache::thrift::detail::st::gen_check_json<
        Bar,
        ::apache::thrift::type_class::variant,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>>,
    "inconsistent use of json option");

static_assert(
    ::apache::thrift::detail::st::gen_check_nimble<
        Bar,
        ::apache::thrift::type_class::structure,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>,
    "inconsistent use of nimble option");
static_assert(
    ::apache::thrift::detail::st::gen_check_nimble<
        Bar,
        ::apache::thrift::type_class::structure,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Foo>>,
    "inconsistent use of nimble option");
static_assert(
    ::apache::thrift::detail::st::gen_check_nimble<
        Bar,
        ::apache::thrift::type_class::variant,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>>,
    "inconsistent use of nimble option");
static_assert(
    ::apache::thrift::detail::st::gen_check_nimble<
        Bar,
        ::apache::thrift::type_class::variant,
        ::apache::thrift::adapt_detail::adapted_t<my::Adapter1, ::cpp2::Baz>>,
    "inconsistent use of nimble option");

} // cpp2
