#include <map>
#include <iostream>

#ifdef TESTING
	#include <gtest/gtest.h>
#endif

#include "application.hpp"

int main(int argc, char **argv) {
	// 
	#ifdef TESTING
		::testing::InitGoogleTest(&argc, argv);
		
		return RUN_ALL_TESTS();

	//
	#else
		Application application(argc, argv);		//
		application.start();
	
		return 0;
	#endif
}