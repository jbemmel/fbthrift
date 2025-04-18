/**
 * Autogenerated by Thrift for src/module.thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated @nocommit
 */

#include "thrift/compiler/test/fixtures/no_metadata/gen-cpp2/module_data.h"

#include <thrift/lib/cpp2/gen/module_data_cpp.h>

namespace apache {
namespace thrift {

const std::array<::cpp2::MyEnum, 2> TEnumDataStorage<::cpp2::MyEnum>::values = {{
  type::MyValue1,
  type::MyValue2,
}};
const std::array<folly::StringPiece, 2> TEnumDataStorage<::cpp2::MyEnum>::names = {{
  "MyValue1",
  "MyValue2",
}};

const std::array<::cpp2::MyUnion::Type, 3> TEnumDataStorage<::cpp2::MyUnion::Type>::values = {{
  type::myEnum,
  type::myStruct,
  type::myDataItem,
}};
const std::array<folly::StringPiece, 3> TEnumDataStorage<::cpp2::MyUnion::Type>::names = {{
  "myEnum",
  "myStruct",
  "myDataItem",
}};

const std::array<folly::StringPiece, 0> TStructDataStorage<::cpp2::MyDataItem>::fields_names = {{
}};
const std::array<int16_t, 0> TStructDataStorage<::cpp2::MyDataItem>::fields_ids = {{
}};
const std::array<protocol::TType, 0> TStructDataStorage<::cpp2::MyDataItem>::fields_types = {{
}};

const std::array<folly::StringPiece, 4> TStructDataStorage<::cpp2::MyStruct>::fields_names = {{
  "MyIntField",
  "MyStringField",
  "MyDataField",
  "myEnum",
}};
const std::array<int16_t, 4> TStructDataStorage<::cpp2::MyStruct>::fields_ids = {{
  1,
  2,
  3,
  4,
}};
const std::array<protocol::TType, 4> TStructDataStorage<::cpp2::MyStruct>::fields_types = {{
  TType::T_I64,
  TType::T_STRING,
  TType::T_STRUCT,
  TType::T_I32,
}};

const std::array<folly::StringPiece, 3> TStructDataStorage<::cpp2::MyUnion>::fields_names = {{
  "myEnum",
  "myStruct",
  "myDataItem",
}};
const std::array<int16_t, 3> TStructDataStorage<::cpp2::MyUnion>::fields_ids = {{
  1,
  2,
  3,
}};
const std::array<protocol::TType, 3> TStructDataStorage<::cpp2::MyUnion>::fields_types = {{
  TType::T_I32,
  TType::T_STRUCT,
  TType::T_STRUCT,
}};

} // namespace thrift
} // namespace apache
