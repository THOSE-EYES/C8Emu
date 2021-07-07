/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

// Include C/C++ STL headers
#include <gtest/gtest.h>

// Include project headers
#include "mocks/mock_cpu.hpp"
#include "fakes/fake_cpu.hpp"

using ::testing::AtLeast;
using ::testing::_;

TEST(CPUTest, CheckExecution) {
	MockCPU mock;

	// Try to call the method
	EXPECT_CALL(mock, execute(_)).Times(AtLeast(1));
	EXPECT_CALL(mock, interrupt()).Times(AtLeast(1));
  	mock.start();
}

TEST_F(FakeCPU, ResetCheck) {
    // Call the method
    reset();

    // Check expected results
    EXPECT_EQ(flags_.running, false);
    EXPECT_EQ(registers_.index, 0);
    EXPECT_EQ(timers_.delay, 0);
    EXPECT_EQ(timers_.sound, 0);
}

TEST_F(FakeCPU, CheckOp_0000) {
    flags_.running = true;

    // Call the method
    _0000();

    // Check the flag
    EXPECT_EQ(flags_.running, false);
}

TEST_F(FakeCPU, CheckOp_00ee) {
    try {
        // Call the method
        _00ee();

        // Fail if the exception is not thrown
        FAIL() << "The stack should be empty";
    }
    catch (const std::exception& e) {
        SUCCEED() << "App crashed successfully";
    }
}

TEST_F(FakeCPU, CheckOp_00e0) {
    // Call the method
    _00e0();
}


TEST_F(FakeCPU, CheckOp_0nnn) {
    // Call the method
    _0nnn();
}

TEST_F(FakeCPU, CheckOp_1nnn) {
    auto offset{0x0BBB};

    // Call the method
    _1nnn(offset);

    // Check the flag
    EXPECT_EQ(offset_, offset);
}

TEST_F(FakeCPU, CheckOp_2nnn) {
    auto offset{0x0BBB};
    auto prev_offset{offset_};

    // Call the method
    _2nnn(offset);

    // Check expected results
    EXPECT_EQ(offset_, offset);
    EXPECT_EQ(prev_offset, stack_->top());
}

TEST_F(FakeCPU, CheckOp_3xnn) {
    auto gen_register{0x1};
    auto value{0x00BB};
    auto prev_offset{offset_};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _3xnn(value | (gen_register << (2 * 4)));

    // Check expected results
    EXPECT_EQ(value, registers_.general->at(gen_register));
    EXPECT_EQ((prev_offset + 2), offset_);
}

TEST_F(FakeCPU, CheckOp_4xnn) {
    auto gen_register{0x1};
    auto value{0x00BB};
    auto prev_offset{offset_};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _4xnn(value | (gen_register << (2 * 4)));

    // Check expected results
    EXPECT_EQ(value, registers_.general->at(gen_register));
    EXPECT_EQ(prev_offset, offset_);
}

TEST_F(FakeCPU, CheckOp_5xy0) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto value{0xBB};
    auto prev_offset{offset_};
    
    // Set internal values
    registers_.general->at(f_register) = value;
    registers_.general->at(s_register) = value;

    // Call the method
    _5xy0((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(value, registers_.general->at(f_register));
    EXPECT_EQ(value, registers_.general->at(s_register));
    EXPECT_EQ((prev_offset + 2), offset_);
}

TEST_F(FakeCPU, CheckOp_6xnn) {
    auto gen_register{0x1};
    auto value{0x00BB};

    // Call the method
    _6xnn(value | (gen_register << (2 * 4)));

    // Check expected results
    EXPECT_EQ(value, registers_.general->at(gen_register));
}

TEST_F(FakeCPU, CheckOp_7xnn) {
    auto gen_register{0x1};
    auto value{0x00BB};
    auto prev_register_value{registers_.general->at(gen_register)};

    // Call the method
    _7xnn(value | (gen_register << (2 * 4)));

    // Check expected results
    EXPECT_EQ(prev_register_value + value,
        registers_.general->at(gen_register));
}

TEST_F(FakeCPU, CheckOp_8xy0) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto value{0xBB};
    
    // Set internal values
    registers_.general->at(s_register) = value;

    // Call the method
    _8xy0((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(f_register),
         registers_.general->at(s_register));
}

TEST_F(FakeCPU, CheckOp_8xy1) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0xCC};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy1((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(f_register),
        (vx_value | vy_value));
}

TEST_F(FakeCPU, CheckOp_8xy2) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0xCC};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy2((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(f_register),
        (vx_value & vy_value));
}

TEST_F(FakeCPU, CheckOp_8xy3) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0xCC};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy3((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(f_register),
        (vx_value ^ vy_value));
}

TEST_F(FakeCPU, CheckOp_8xy4) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0xCC};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy4((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(0xF), 1);
}

TEST_F(FakeCPU, CheckOp_8xy5) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0x11};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy5((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(0xF), 1);
}

TEST_F(FakeCPU, CheckOp_8xy6) {
    auto gen_register{0x1};
    auto value{0xBB};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _8xy6(gen_register << 8);

    // Check expected results
    EXPECT_EQ(registers_.general->at(0xF), 1);
    EXPECT_EQ(registers_.general->at(gen_register), (value >> 1));
}

TEST_F(FakeCPU, CheckOp_8xy7) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0x11};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _8xy7((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ(registers_.general->at(0xF), 0);
    EXPECT_EQ(registers_.general->at(f_register),
        static_cast<uint8_t>(vy_value - vx_value));
}

TEST_F(FakeCPU, CheckOp_8xye) {
    auto gen_register{0x1};
    auto value{0x01};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _8xye(gen_register << 8);

    // Check expected results
    EXPECT_EQ(registers_.general->at(0xF), 0);
    EXPECT_EQ(registers_.general->at(gen_register), 
        (value << 1));
}

TEST_F(FakeCPU, CheckOp_9xy0) {
    auto f_register{0x1};
    auto s_register{0x2};
    auto vx_value{0xBB};
    auto vy_value{0x11};
    auto prev_offset{offset_};
    
    // Set internal values
    registers_.general->at(f_register) = vx_value;
    registers_.general->at(s_register) = vy_value;

    // Call the method
    _9xy0((f_register << 8) | (s_register << 4));

    // Check expected results
    EXPECT_EQ((prev_offset + 2), offset_);
}

TEST_F(FakeCPU, CheckOp_annn) {
    auto offset{0x0BBB};

    // Call the method
    _annn(offset);

    // Check the flag
    EXPECT_EQ(registers_.index, offset);
}

TEST_F(FakeCPU, CheckOp_bnnn) {
    auto value{0x5};
    auto offset{0x0BBB};
    auto prev_offset{offset_};

    // Set internal values
    registers_.general->at(0) = value;

    // Call the method
    _bnnn(offset);

    // Check the flag
    EXPECT_EQ((offset + value), offset_);
}

TEST_F(FakeCPU, CheckOp_cxnn) {
    auto value{0x5};
    auto gen_register{0x1};

    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _cxnn(gen_register << 8);

    // Check the flag
    ASSERT_NE(value, registers_.general->at(gen_register));
}

TEST_F(FakeCPU, CheckOp_dxyn) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_ex9e) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_exa1) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_fx07) {
    auto gen_register{0x1};
    auto value{0xBB};
    
    // Set internal values
    timers_.delay = value;

    // Call the method
    _fx07(gen_register << 8);

    // Check expected results
    EXPECT_EQ(value, registers_.general->at(gen_register));
}

TEST_F(FakeCPU, CheckOp_fx0a) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_fx15) {
    auto gen_register{0x1};
    auto value{0xBB};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _fx15(gen_register << 8);

    // Check expected results
    EXPECT_EQ(value, timers_.delay);
}

TEST_F(FakeCPU, CheckOp_fx18) {
    auto gen_register{0x1};
    auto value{0xBB};
    
    // Set internal values
    registers_.general->at(gen_register) = value;

    // Call the method
    _fx18(gen_register << 8);

    // Check expected results
    EXPECT_EQ(value, timers_.sound);
}

TEST_F(FakeCPU, CheckOp_fx1e) {
    auto gen_register{0x1};
    auto vx_value{0xBB};
    auto i_value{0x1};
    
    // Set internal values
    registers_.general->at(gen_register) = vx_value;
    registers_.index = i_value;

    // Call the method
    _fx1e(gen_register << 8);

    // Check expected results
    EXPECT_EQ((vx_value + i_value), registers_.index);
}

TEST_F(FakeCPU, CheckOp_fx29) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_fx33) {
    // FIXME : todo

    FAIL() << "Not implemented yet. Can't be tested";
}

TEST_F(FakeCPU, CheckOp_fx55) {
    auto gen_register{0x05};

    // Set internal values
    registers_.index = 0;
    for (auto vx{0}; vx <= gen_register; ++vx)
        registers_.general->at(vx) = vx;

    // Call the method
    _fx55(gen_register << 8);

    // Check expected results
    for (auto vx{0}; vx <= gen_register; ++vx)
        EXPECT_EQ(registers_.general->at(vx), 
            ram_->at(registers_.index + vx));
}

TEST_F(FakeCPU, CheckOp_fx65) {
    auto gen_register{0x05};

    // Set internal values
    registers_.index = 0;
    for (auto vx{0}; vx <= gen_register; ++vx)
        ram_->at(registers_.index + vx) = vx;

    // Call the method
    _fx65(gen_register << 8);

    // Check expected results
    for (auto vx{0}; vx <= gen_register; ++vx)
        EXPECT_EQ(registers_.general->at(vx), 
            ram_->at(registers_.index + vx));
}