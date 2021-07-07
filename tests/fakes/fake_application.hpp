// Include Gtest headers
#include <gtest/gtest.h>

// Include project headers
#include "application.hpp"

/**
 * FakeApplication class is used to test private and protected
 * methods of Application class
 */
class FakeApplication : 
	public application::Application, public testing::Test {
public:
	/**
	 * Constructor
	 */
	FakeApplication() : 
		Application("test"), Test() {}
};