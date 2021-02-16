#include <gtest/gtest.h>

#include <string>
#include "tokenizer.hpp"

const std::string KEY = "test";

TEST(TokenizerTest, NotFoundExc) {
    Tokenizer<std::string, std::string> tokenizer;
    tokenizer.parse(1, new char*[1]);
    
    try {
        // Try to get a value
        tokenizer.getValue(KEY);

        // Fail the test if there is no exception
        FAIL() << "Expected Exception with code : " << TNOTFOUND;
    }
    catch (Exception const& err) {
		// Expected an exception with a predefined index
		EXPECT_EQ(err.what(), std::string(" An error has occured. The code of the error is : ") + std::to_string(TNOTFOUND));
	}
}