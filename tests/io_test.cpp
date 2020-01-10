#include <gtest/gtest.h>

#include "io.h"
#include "memory.h"
#include "exceptions.h"

TEST(IOTest, WrongFile) {
	ASSERT_DEATH(load("test.txt", new Memory()), " An error has occured. The code of the error is : 6");
}