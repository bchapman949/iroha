/**
 * Copyright Soramitsu Co., Ltd. 2018 All Rights Reserved.
 * http://soramitsu.co.jp
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include "builders/common_objects/peer_builder.hpp"
#include "builders/protobuf/common_objects/proto_peer_builder.hpp"
#include "validators/field_validator.hpp"

// TODO: 14.02.2018 nickaleks mock builder implementation IR-970
// TODO: 14.02.2018 nickaleks mock field validator IR-971

TEST(PeerBuilderTest, StatelessValidAddressCreation) {

  shared_model::builder::PeerBuilder<shared_model::proto::PeerBuilder,
                                     shared_model::validation::FieldValidator>
      builder;

  auto valid_address = "127.0.0.1:1337";
  shared_model::interface::types::PubkeyType key(std::string(32, '0'));
  auto peer = builder.address(valid_address).pubkey(key).build();
  peer.match(
      [&](shared_model::builder::BuilderResult<shared_model::interface::Peer>::ValueType &v) {
        EXPECT_EQ(v.value->address(), valid_address);
      },
      [](shared_model::builder::BuilderResult<shared_model::interface::Peer>::ErrorType &e) { FAIL() << *e.error; });
}
