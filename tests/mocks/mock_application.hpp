// Include Gtest headers
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include project headers
#include "application.hpp"

class MockApplication : public application::Application {
public:
	/**
	 * Constructor
	 */
	MockApplication(const std::string& filename) : 
		Application(filename) {}

public:
	/**
	 * Mocking the load() method
	 */
	MOCK_METHOD0(load, void());
};
