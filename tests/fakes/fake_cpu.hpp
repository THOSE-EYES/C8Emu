// Include Gtest headers
#include <gtest/gtest.h>

// Include project headers
#include "hw/cpu.hpp"

/**
 * FakeCPU class is used to test private and protected
 * methods of CPU class
 */
class FakeCPU : 
	public application::hw::CPU, public testing::Test {
	// Nothing to do here
};