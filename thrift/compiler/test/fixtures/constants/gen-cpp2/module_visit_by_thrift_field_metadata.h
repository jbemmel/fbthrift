/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include <thrift/lib/cpp2/visitation/visit_by_thrift_field_metadata.h>
#include "thrift/compiler/test/fixtures/constants/gen-cpp2/module_metadata.h"

namespace apache {
namespace thrift {
namespace detail {

template <>
struct VisitByFieldId<::cpp2::Internship> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).weeks_ref());
    case 2:
      return f(1, static_cast<T&&>(t).title_ref());
    case 3:
      return f(2, static_cast<T&&>(t).employer_ref());
    case 4:
      return f(3, static_cast<T&&>(t).compensation_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::Internship");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::Range> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).min_ref());
    case 2:
      return f(1, static_cast<T&&>(t).max_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::Range");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::struct1> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).a_ref());
    case 2:
      return f(1, static_cast<T&&>(t).b_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::struct1");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::struct2> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).a_ref());
    case 2:
      return f(1, static_cast<T&&>(t).b_ref());
    case 3:
      return f(2, static_cast<T&&>(t).c_ref());
    case 4:
      return f(3, static_cast<T&&>(t).d_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::struct2");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::struct3> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).a_ref());
    case 2:
      return f(1, static_cast<T&&>(t).b_ref());
    case 3:
      return f(2, static_cast<T&&>(t).c_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::struct3");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::struct4> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).a_ref());
    case 2:
      return f(1, static_cast<T&&>(t).b_ref());
    case 3:
      return f(2, static_cast<T&&>(t).c_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::struct4");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::union1> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).i_ref());
    case 2:
      return f(1, static_cast<T&&>(t).d_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::union1");
    }
  }
};

template <>
struct VisitByFieldId<::cpp2::union2> {
  template <typename F, typename T>
  void operator()(FOLLY_MAYBE_UNUSED F&& f, int32_t fieldId, FOLLY_MAYBE_UNUSED T&& t) const {
    switch (fieldId) {
    case 1:
      return f(0, static_cast<T&&>(t).i_ref());
    case 2:
      return f(1, static_cast<T&&>(t).d_ref());
    case 3:
      return f(2, static_cast<T&&>(t).s_ref());
    case 4:
      return f(3, static_cast<T&&>(t).u_ref());
    default:
      throwInvalidThriftId(fieldId, "::cpp2::union2");
    }
  }
};
} // namespace detail
} // namespace thrift
} // namespace apache
