#include <map>
#include <iostream>

#ifdef TESTING
	#include <gtest/gtest.h>
#endif

#include "application.h"

int main(int argc, char **argv) {
	// 
	#ifdef TESTING
		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();

	//
	#else
		Application application(argc, argv);		//
		application.start();
	#endif

	return 0;
}