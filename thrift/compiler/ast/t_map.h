/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <thrift/compiler/ast/t_container.h>

namespace apache {
namespace thrift {
namespace compiler {

/**
 * A map is a lightweight container type that just wraps another two data
 * types.
 *
 */
class t_map : public t_container {
 public:
  t_map(t_type_ref key_type, t_type_ref val_type)
      : key_type_(std::move(key_type)), val_type_(std::move(val_type)) {}

  const t_type* get_key_type() const {
    return key_type_.get_type();
  }

  const t_type* get_val_type() const {
    return val_type_.get_type();
  }

  std::string get_full_name() const override {
    return (
        "map<" + key_type_.get_type()->get_full_name() + ", " +
        val_type_.get_type()->get_full_name() + ">");
  }

  t_type::type get_type_value() const override {
    return t_type::type::t_map;
  }

 private:
  t_type_ref key_type_;
  t_type_ref val_type_;

 public:
  // TODO(afuller): Delete everything below here. It is only provided for
  // backwards compatibility.

  t_map(const t_type* key_type, const t_type* val_type)
      : t_map(t_type_ref(key_type), t_type_ref(val_type)) {}
};

} // namespace compiler
} // namespace thrift
} // namespace apache
