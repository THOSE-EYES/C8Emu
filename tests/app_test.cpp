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

// Include Gtest headers
#include <gtest/gtest.h>

// Include C/C++ STL headers
#include <string>
#include <memory>

// Include project headers
#include "fakes/fake_application.hpp"
#include "mocks/mock_application.hpp"

TEST_F(FakeApplication, CheckFilename) {
	auto filename{"test.txt"};
	set_file(filename);

	// Check the file
	EXPECT_EQ(filename, get_file());
}

TEST_F(FakeApplication, WrongFile) {
	auto filename{"test.txt"};
	set_file(filename);

	// Try to load the file
	try {
		load();

		FAIL() << "The app shouldn't have started. The file is not present in the system";
	}
	catch (const std::runtime_error& e) {
		SUCCEED() << "App crashed successfully!";
	}	
} 

TEST(AppTest, CheckLoadCalling) {
	MockApplication mock{"../tests/program/demo.ch8"};

	// Try to call the method
	EXPECT_CALL(mock, load()).Times(1);
  	mock.start();
}