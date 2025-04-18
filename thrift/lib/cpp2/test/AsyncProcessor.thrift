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

service Parent {
  i32 parentMethod1();
  stream<i32> parentMethod2();
  i32 parentMethod3();
}

interaction Interaction {
  i32 interactionMethod();
}

service Child extends Parent {
  performs Interaction;
  oneway void childMethod1();
  string childMethod2();
}

service DummyMonitor {
  i64 getCounter();
}
