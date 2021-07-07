#include <map>
#include <iostream>

#ifdef TESTING
	#include <gtest/gtest.h>
#endif

#include "application.hpp"

int main(int argc, char **argv) {
	// Run the tests
	#ifdef TESTING
		::testing::InitGoogleTest(&argc, argv);
		
		return RUN_ALL_TESTS();

	// Run the app
	#else
		if (argc != 2)
			throw std::invalid_argument("Not enough arguments");

		std::string filename = std::string(argv[1]); 

		// Start the execution
		application::Application application(filename);
		application.start();
	
		return 0;
	#endif
}