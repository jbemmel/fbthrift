/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include <thrift/lib/cpp2/gen/module_constants_h.h>

#include "thrift/compiler/test/fixtures/doctext/gen-cpp2/module_types.h"

namespace cpp2 {

struct module_constants {

  // consider using folly::StringPiece instead of std::string whenever possible
  // to referencing this statically allocated string constant, in order to
  // prevent unnecessary allocations

  static constexpr char const * const FOO_ = "foo";

  static constexpr char const * FOO() {
    return FOO_;
  }

  static constexpr ::std::int32_t const BAR_ = 123;

  static constexpr ::std::int32_t BAR() {
    return BAR_;
  }

  static constexpr ::std::int32_t const BIFF_ = 0;

  static constexpr ::std::int32_t BIFF() {
    return BIFF_;
  }

  static constexpr ::std::int32_t const SHOUTY_ = 11;

  static constexpr ::std::int32_t SHOUTY() {
    return SHOUTY_;
  }

};

} // cpp2
