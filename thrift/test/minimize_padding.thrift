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

namespace cpp2 apache.thrift.test

struct empty {
} (cpp.minimize_padding)

enum test_enum {
  foo = 0,
}

struct nonoptimal {
  1: required i16 a;
  2: required bool b;
  3: required i32 c;
  4: required byte d;
  5: required i64 e;
  6: required test_enum f;
  7: required double g;
  8: required float h;
  9: required string i;
  10: required byte j;
  11: required list<byte> k;
  12: required byte l;
  13: required set<byte> m;
  14: required byte n;
  15: required map<byte, byte> o;

  // Add extra fields to make the size of this struct a multiple of 8 (assuming
  // containers' alignment is 8) and reducing the room for reordering error.
  16: required byte p;
  17: required i32 q;
} (cpp.minimize_padding)

struct small_align {
  1: required byte a;
  2: required byte b;
}

struct big_align {
  1: required byte a;
  2: required i32 b;
}

struct nonoptimal_struct {
  1: required byte small;
  2: required big_align big;
  3: required small_align medium;
} (cpp.minimize_padding)

struct same_sizes {
  1: required i32 a;
  2: required i32 b;
  3: required i32 c;
  4: required i32 d;
} (cpp.minimize_padding)

struct ref_type {
  1: required byte a;
  2: required byte b (cpp.ref_type = "unique");
  3: required byte c;
  4: required byte d (cpp2.ref_type = "unique");
} (cpp.minimize_padding)

struct nonoptimal_struct_noexcept_move {
  1: required byte small;
  2: required big_align big;
  3: required small_align medium;
} (cpp.minimize_padding)

struct nonoptimal_large_struct_noexcept_move {
  1: required byte small;
  2: required big_align big;
  3: required small_align medium;
  4: required string mystring;
  5: required i32 a;
} (cpp.minimize_padding)
