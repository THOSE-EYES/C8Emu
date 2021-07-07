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