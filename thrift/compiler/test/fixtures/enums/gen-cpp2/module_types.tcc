/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include "thrift/compiler/test/fixtures/enums/gen-cpp2/module_types.h"

#include <thrift/lib/cpp2/gen/module_types_tcc.h>

namespace cpp2 {

} // cpp2
namespace std {

} // std


namespace apache {
namespace thrift {
namespace detail {

template <>
struct TccStructTraits<::cpp2::SomeStruct> {
  static void translateFieldName(
      folly::StringPiece _fname,
      int16_t& fid,
      apache::thrift::protocol::TType& _ftype) noexcept;
};

} // namespace detail
} // namespace thrift
} // namespace apache

namespace cpp2 {

template <class Protocol_>
void SomeStruct::readNoXfer(Protocol_* iprot) {
  apache::thrift::detail::ProtocolReaderStructReadState<Protocol_> _readState;

  _readState.readStructBegin(iprot);

  using apache::thrift::TProtocolException;


  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          0,
          1,
          apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_reasonable:
  {
    ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::readWithContext(*iprot, this->reasonable, _readState);
    
  }
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  this->__isset.reasonable = true;
  THRIFT_IGNORE_ISSET_USE_WARNING_END

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          1,
          2,
          apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_fine:
  {
    ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::readWithContext(*iprot, this->fine, _readState);
    
  }
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  this->__isset.fine = true;
  THRIFT_IGNORE_ISSET_USE_WARNING_END

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          2,
          3,
          apache::thrift::protocol::T_I32))) {
    goto _loop;
  }
_readField_questionable:
  {
    ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::readWithContext(*iprot, this->questionable, _readState);
    
  }
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  this->__isset.questionable = true;
  THRIFT_IGNORE_ISSET_USE_WARNING_END

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          3,
          4,
          apache::thrift::protocol::T_SET))) {
    goto _loop;
  }
_readField_tags:
  {
    _readState.beforeSubobject(iprot);
    this->tags = ::std::set<::std::int32_t>();
    ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::set<::apache::thrift::type_class::integral>, ::std::set<::std::int32_t>>::readWithContext(*iprot, this->tags, _readState);
    _readState.afterSubobject(iprot);
    
  }
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  this->__isset.tags = true;
  THRIFT_IGNORE_ISSET_USE_WARNING_END

  if (UNLIKELY(!_readState.advanceToNextField(
          iprot,
          4,
          0,
          apache::thrift::protocol::T_STOP))) {
    goto _loop;
  }

_end:
  _readState.readStructEnd(iprot);

  return;

_loop:
  _readState.afterAdvanceFailure(iprot);
  if (_readState.atStop()) {
    goto _end;
  }
  if (iprot->kUsesFieldNames()) {
    _readState.template fillFieldTraitsFromName<apache::thrift::detail::TccStructTraits<SomeStruct>>();
  }

  switch (_readState.fieldId) {
    case 1:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_reasonable;
      } else {
        goto _skip;
      }
    }
    case 2:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_fine;
      } else {
        goto _skip;
      }
    }
    case 3:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_I32))) {
        goto _readField_questionable;
      } else {
        goto _skip;
      }
    }
    case 4:
    {
      if (LIKELY(_readState.isCompatibleWithType(iprot, apache::thrift::protocol::T_SET))) {
        goto _readField_tags;
      } else {
        goto _skip;
      }
    }
    default:
    {
_skip:
      _readState.skip(iprot);
      _readState.readFieldEnd(iprot);
      _readState.readFieldBeginNoInline(iprot);
      goto _loop;
    }
  }
}

template <class Protocol_>
uint32_t SomeStruct::serializedSize(Protocol_ const* prot_) const {
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("SomeStruct");
  {
    xfer += prot_->serializedFieldSize("reasonable", apache::thrift::protocol::T_I32, 1);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->reasonable);
  }
  {
    xfer += prot_->serializedFieldSize("fine", apache::thrift::protocol::T_I32, 2);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->fine);
  }
  {
    xfer += prot_->serializedFieldSize("questionable", apache::thrift::protocol::T_I32, 3);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->questionable);
  }
  {
    xfer += prot_->serializedFieldSize("tags", apache::thrift::protocol::T_SET, 4);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::set<::apache::thrift::type_class::integral>, ::std::set<::std::int32_t>>::serializedSize<false>(*prot_, this->tags);
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
  THRIFT_IGNORE_ISSET_USE_WARNING_END
}

template <class Protocol_>
uint32_t SomeStruct::serializedSizeZC(Protocol_ const* prot_) const {
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  uint32_t xfer = 0;
  xfer += prot_->serializedStructSize("SomeStruct");
  {
    xfer += prot_->serializedFieldSize("reasonable", apache::thrift::protocol::T_I32, 1);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->reasonable);
  }
  {
    xfer += prot_->serializedFieldSize("fine", apache::thrift::protocol::T_I32, 2);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->fine);
  }
  {
    xfer += prot_->serializedFieldSize("questionable", apache::thrift::protocol::T_I32, 3);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::serializedSize<false>(*prot_, this->questionable);
  }
  {
    xfer += prot_->serializedFieldSize("tags", apache::thrift::protocol::T_SET, 4);
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::set<::apache::thrift::type_class::integral>, ::std::set<::std::int32_t>>::serializedSize<false>(*prot_, this->tags);
  }
  xfer += prot_->serializedSizeStop();
  return xfer;
  THRIFT_IGNORE_ISSET_USE_WARNING_END
}

template <class Protocol_>
uint32_t SomeStruct::write(Protocol_* prot_) const {
  THRIFT_IGNORE_ISSET_USE_WARNING_BEGIN
  uint32_t xfer = 0;
  xfer += prot_->writeStructBegin("SomeStruct");
  bool previousFieldHasValue = true;
  {
    constexpr int16_t kPrevFieldId = 0;
    xfer += ::apache::thrift::detail::writeFieldBegin<apache::thrift::protocol::T_I32, 1, kPrevFieldId>(*prot_, "reasonable", previousFieldHasValue);
    previousFieldHasValue = true;
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::write(*prot_, this->reasonable);
    xfer += prot_->writeFieldEnd();
  }
  {
    constexpr int16_t kPrevFieldId = 1;
    xfer += ::apache::thrift::detail::writeFieldBegin<apache::thrift::protocol::T_I32, 2, kPrevFieldId>(*prot_, "fine", previousFieldHasValue);
    previousFieldHasValue = true;
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::write(*prot_, this->fine);
    xfer += prot_->writeFieldEnd();
  }
  {
    constexpr int16_t kPrevFieldId = 2;
    xfer += ::apache::thrift::detail::writeFieldBegin<apache::thrift::protocol::T_I32, 3, kPrevFieldId>(*prot_, "questionable", previousFieldHasValue);
    previousFieldHasValue = true;
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::enumeration, ::cpp2::Metasyntactic>::write(*prot_, this->questionable);
    xfer += prot_->writeFieldEnd();
  }
  {
    constexpr int16_t kPrevFieldId = 3;
    xfer += ::apache::thrift::detail::writeFieldBegin<apache::thrift::protocol::T_SET, 4, kPrevFieldId>(*prot_, "tags", previousFieldHasValue);
    previousFieldHasValue = true;
    xfer += ::apache::thrift::detail::pm::protocol_methods<::apache::thrift::type_class::set<::apache::thrift::type_class::integral>, ::std::set<::std::int32_t>>::write(*prot_, this->tags);
    xfer += prot_->writeFieldEnd();
  }
  xfer += prot_->writeFieldStop();
  xfer += prot_->writeStructEnd();
  return xfer;
  THRIFT_IGNORE_ISSET_USE_WARNING_END
}

extern template void SomeStruct::readNoXfer<>(apache::thrift::BinaryProtocolReader*);
extern template uint32_t SomeStruct::write<>(apache::thrift::BinaryProtocolWriter*) const;
extern template uint32_t SomeStruct::serializedSize<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template uint32_t SomeStruct::serializedSizeZC<>(apache::thrift::BinaryProtocolWriter const*) const;
extern template void SomeStruct::readNoXfer<>(apache::thrift::CompactProtocolReader*);
extern template uint32_t SomeStruct::write<>(apache::thrift::CompactProtocolWriter*) const;
extern template uint32_t SomeStruct::serializedSize<>(apache::thrift::CompactProtocolWriter const*) const;
extern template uint32_t SomeStruct::serializedSizeZC<>(apache::thrift::CompactProtocolWriter const*) const;

} // cpp2
