/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */
#pragma once

#include  "thrift/compiler/test/fixtures/types/gen-cpp2/include_fatal_types.h"

#include "thrift/compiler/test/fixtures/types/gen-cpp2/module_types.h"
#include "thrift/compiler/test/fixtures/types/gen-cpp2/module_fatal.h"

#include <fatal/type/enum.h>
#include <fatal/type/variant_traits.h>

#include <type_traits>

namespace apache { namespace thrift { namespace fixtures { namespace types {

namespace __fbthrift_refl {
namespace __fbthrift_refl_impl = ::apache::thrift::detail::reflection_impl;
class NoExceptMoveUnion_tenum_traits {
 public:
  using type = ::apache::thrift::fixtures::types::NoExceptMoveUnion::Type;

 private:
  struct __fbthrift_value_string_field {
    using name = __fbthrift_strings_module::__fbthrift_hash_d7c1fe391a8c7ceef0c2058b8163eae35e230e7ecf528cd41a09100a7aaa4fce;
    using value = std::integral_constant<type, type::string_field>;
    using annotations = __fbthrift_refl_impl::no_annotations;
  };

  struct __fbthrift_value_i32_field {
    using name = __fbthrift_strings_module::__fbthrift_hash_463a2e2458322db48dcc738e6792afe31f8fb1883cd29f0ecae7719e93de0818;
    using value = std::integral_constant<type, type::i32_field>;
    using annotations = __fbthrift_refl_impl::no_annotations;
  };

  struct __fbthrift_member {
    using string_field = __fbthrift_value_string_field;
    using i32_field = __fbthrift_value_i32_field;
  };

 public:
  using name = __fbthrift_strings_module::Type;
  using member = __fbthrift_member;
  using fields = ::fatal::list<
      member::string_field,
      member::i32_field
  >;

  using annotations = __fbthrift_refl_impl::no_annotations;

  static char const *to_string(type e, char const *fallback) {
    switch (e) {
      case type::string_field: return "string_field";
      case type::i32_field: return "i32_field";
      default: return fallback;
    }
  }
};

class NoExceptMoveUnion_variant_traits {
 private:
  struct __fbthrift_ids {
    using string_field = std::integral_constant<::apache::thrift::fixtures::types::NoExceptMoveUnion::Type, ::apache::thrift::fixtures::types::NoExceptMoveUnion::Type::string_field>;
    using i32_field = std::integral_constant<::apache::thrift::fixtures::types::NoExceptMoveUnion::Type, ::apache::thrift::fixtures::types::NoExceptMoveUnion::Type::i32_field>;
  };

  struct __fbthrift_member_string_field {
    using name = __fbthrift_strings_module::__fbthrift_hash_d7c1fe391a8c7ceef0c2058b8163eae35e230e7ecf528cd41a09100a7aaa4fce;
    static constexpr ::apache::thrift::field_id_t id = 1;
    using type_class = ::apache::thrift::type_class::string;
    struct setter {
      template <typename... Args>
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &variant, Args &&...args) const {
        return variant.set_string_field(std::forward<Args>(args)...);
      }
    };
    struct getter {
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion const &variant) const {
        return variant.get_string_field();
      }
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &variant) const {
        return variant.mutable_string_field();
      }
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &&variant) const {
        return std::move(variant).move_string_field();
      }
    };
  };
  struct __fbthrift_member_i32_field {
    using name = __fbthrift_strings_module::__fbthrift_hash_463a2e2458322db48dcc738e6792afe31f8fb1883cd29f0ecae7719e93de0818;
    static constexpr ::apache::thrift::field_id_t id = 2;
    using type_class = ::apache::thrift::type_class::integral;
    struct setter {
      template <typename... Args>
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &variant, Args &&...args) const {
        return variant.set_i32_field(std::forward<Args>(args)...);
      }
    };
    struct getter {
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion const &variant) const {
        return variant.get_i32_field();
      }
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &variant) const {
        return variant.mutable_i32_field();
      }
      decltype(auto) operator ()(::apache::thrift::fixtures::types::NoExceptMoveUnion &&variant) const {
        return std::move(variant).move_i32_field();
      }
    };
  };

 public:
  using type = ::apache::thrift::fixtures::types::NoExceptMoveUnion;
  using name = __fbthrift_strings_module::NoExceptMoveUnion;
  using id = type::Type;
  using ids = __fbthrift_ids;
  using descriptors = ::fatal::list<
      ::fatal::variant_member_descriptor<
          ::std::string,
           __fbthrift_ids::string_field,
          __fbthrift_member_string_field::getter,
          __fbthrift_member_string_field::setter,
          ::apache::thrift::reflected_variant_member_metadata<__fbthrift_member_string_field>>,
      ::fatal::variant_member_descriptor<
          ::std::int32_t,
           __fbthrift_ids::i32_field,
          __fbthrift_member_i32_field::getter,
          __fbthrift_member_i32_field::setter,
          ::apache::thrift::reflected_variant_member_metadata<__fbthrift_member_i32_field>>
  >;

  class annotations {
    struct __fbthrift_keys {
      using cpp_noexcept_move = __fbthrift_strings_module::cpp_noexcept_move;
    };

    struct __fbthrift_values {
      using cpp_noexcept_move = ::fatal::sequence<char, '1'>;
    };

   public:
    using keys = __fbthrift_keys;
    using values = __fbthrift_values;
    using map = ::fatal::list<
        ::apache::thrift::annotation<keys::cpp_noexcept_move, values::cpp_noexcept_move>
    >;
  };

  static id get_id(type const &variant) {
    return variant.getType();
  }

  static bool empty(type const &variant) {
    return variant.getType() == id::__EMPTY__;
  }

  static void clear(type &variant) {
    return variant.__clear();
  }
};
} // __fbthrift_refl

FATAL_REGISTER_ENUM_TRAITS(
  __fbthrift_refl::NoExceptMoveUnion_tenum_traits,
  ::apache::thrift::detail::type_common_metadata_impl<
      module_tags::module,
      ::apache::thrift::reflected_annotations<__fbthrift_refl::NoExceptMoveUnion_tenum_traits::annotations>,
      static_cast<::apache::thrift::legacy_type_id_t>(0ull)
  >
);
FATAL_REGISTER_VARIANT_TRAITS(
  __fbthrift_refl::NoExceptMoveUnion_variant_traits,
  ::apache::thrift::detail::type_common_metadata_impl<
      module_tags::module,
      ::apache::thrift::reflected_annotations<__fbthrift_refl::NoExceptMoveUnion_variant_traits::annotations>,
      static_cast<::apache::thrift::legacy_type_id_t>(2244191815193815340ull)
  >
);
}}}} // apache::thrift::fixtures::types
