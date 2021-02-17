#include <map>
#include <iostream>

#ifdef TESTING
	#include <gtest/gtest.h>
#endif

#include "application.hpp"

/**
 * 
 */
int main(int argc, char **argv) {
	// 
	#ifdef TESTING
		::testing::InitGoogleTest(&argc, argv);
		
		return RUN_ALL_TESTS();

	//
	#else
		if (argc != 2)
			throw new std::invalid_argument("Not enough arguments");

		std::string filename = std::string(argv[1]); 
		Application application(filename);

		//
		application.start();
	
		return 0;
	#endif
}