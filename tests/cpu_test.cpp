#include <gtest/gtest.h>

#include <string>
#include "cpu.hpp"

const short WRONGOP = 0xf066;

// TODO : create a mock class

/*
TEST(CPUTest, WrongOpcode) {
    RAM* memory = new RAM(MEM_SIZE);
    Stack* stack = new Stack(STACK_SIZE);
    CPU* cpu = new CPU(memory, stack);

    try {
        //
        cpu->execute(WRONGOP);

        // Fail the test if there is no exception
        FAIL() << "Expected Exception with code : " << STWRONGSZ;
    }
    catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(OPCODEERR));
	}
}
*/

TEST(CPUTest, NullptrExc) {
    try {
        // Create an instance of CPU with null pointers
        CPU* cpu = new CPU(nullptr, nullptr);

        // Fail the test if there is no exception
        FAIL() << "Expected Exception with code : " << NULLPTRERR;
    }
    catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(NULLPTRERR));
	}
}