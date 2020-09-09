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

#include <thrift/conformance/cpp2/Protocol.h>

#include <folly/lang/Exception.h>

namespace apache::thrift::conformance {

std::optional<StandardProtocol> getStandardProtocol(
    const std::string& name) noexcept {
  if (name.empty()) {
    // Interpreted as None.
    return StandardProtocol::None;
  }

  StandardProtocol result;
  if (!apache::thrift::TEnumTraits<StandardProtocol>::findValue(
          name.c_str(), &result)) {
    // Not a known standard protocol.
    return std::nullopt;
  }

  // It is a standard protocol!
  return result;
}

Protocol::Protocol(std::string name) noexcept : custom_(std::move(name)) {
  if (apache::thrift::TEnumTraits<StandardProtocol>::findValue(
          custom_.c_str(), &standard_)) {
    // Actually a standard protocol.
    custom_ = {};
  }
}

Protocol::Protocol(ProtocolStruct protocolStruct) noexcept
    : standard_(*protocolStruct.standard_ref()) {
  if (standard_ == StandardProtocol::None &&
      protocolStruct.custom_ref().has_value()) {
    // Has a custom name, try to convert it to a standard protocol.
    if (!apache::thrift::TEnumTraits<StandardProtocol>::findValue(
            protocolStruct.custom_ref().value_unchecked().c_str(),
            &standard_)) {
      // Not a standard protocol, so store the custom name.
      custom_ = std::move(protocolStruct.custom_ref().value_unchecked());
    }
  }
}

std::string_view Protocol::name() const noexcept {
  if (!custom_.empty()) {
    return custom_;
  }
  if (const char* name =
          apache::thrift::TEnumTraits<StandardProtocol>::findName(standard_)) {
    return name;
  }

  // Unknown standard protocol.
  return {};
}

ProtocolStruct Protocol::asStruct() const noexcept {
  ProtocolStruct result;
  if (!custom_.empty()) {
    result.custom_ref() = custom_;
  } else {
    result.standard_ref() = standard_;
  }
  return result;
}

bool operator<(const Protocol& lhs, const Protocol& rhs) {
  if (lhs.standard() < rhs.standard()) {
    return true;
  }
  if (lhs.standard() > rhs.standard()) {
    return false;
  }
  return lhs.custom() < rhs.custom();
}

} // namespace apache::thrift::conformance
