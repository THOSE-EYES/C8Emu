#include <gtest/gtest.h>

#include <string>
#include "stack.hpp"

const int STACK_SIZE = 1;
const short WORD = 0x01;

TEST(StackTest, ZeroSize) {
    try {
        // Create an instance of Stack with size == 0
        Stack* stack = new Stack(0);

        // Fail the test if there is no exception
        FAIL() << "Expected Exception with code : " << STWRONGSZERR;
    }
    catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(STWRONGSZERR));
	}
}

TEST(StackTest, StoringDataExc) {
	Stack* stack = new Stack(STACK_SIZE);		// Instance of Stack memory

    // Make the stack full
    stack->store(WORD);

	try {
        // Try to store data inside of the full stack
	    stack->store(WORD);

		// Fail the test if there is no exception
		FAIL() << "Expected Exception with code : " << STFULLERROR;
	}
	catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(STFULLERROR));
	}
}

TEST(StackTest, RetrievingDataExc) {
	Stack* stack = new Stack(STACK_SIZE);		// Instance of Stack memory
	
    // Store some data in the Stack
    stack->store(WORD);

    // Remove the only entry from the stack(ignoring the data)
    stack->remove();

	try {
        // Try to remove data from the empty stack
        stack->remove();

		// Fail the test if there is no exception
		FAIL() << "Expected Exception with code : " << STEMPTYERROR;
	}
	catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(STEMPTYERROR));
	}
}