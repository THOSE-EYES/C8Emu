#include <gtest/gtest.h>

#include <string>
#include "ram.hpp"

const int MEM_SIZE = 1;
const char BYTE = 0x1;

TEST(VirtualRAMTest, ZeroSizeExc) {
	try {
		// Try to create a RAM instance with size = 0
		RAM* memory = new RAM(0);

		// Fail the test if there is no exception
		FAIL() << "Expected Exception with code : " << SMALLMEMSZERR;
	}
	catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(SMALLMEMSZERR));
	}
}

TEST(VirtualRAMTest, MovingIndex) {
	RAM* memory = new RAM(MEM_SIZE);		// Instance of RAM memory
	
	try {
		// Try to move the index beyond memory size
		memory->move(MEM_SIZE);

		// Fail the test if there is no exception
		FAIL() << "Expected Exception with code : " << MEMRANGEOUTERR;
	}
	catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(MEMRANGEOUTERR));
	}
}

TEST(VirtualRAMTest, IOTest) {
	RAM* memory = new RAM(MEM_SIZE);		// Instance of RAM memory

	// Write the byte to the memory
	memory->write(BYTE);

	// Check if the byte is returned correctly
	ASSERT_EQ(memory->read(), BYTE);
}