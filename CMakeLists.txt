#Setting CMake
cmake_minimum_required(VERSION 3.15)
project(CHIP-8)
option(DEBUG "Debug variable used to build tests with the project" OFF)

#Setting the compiler
set(CMAKE_CXX_COMPILER "g++")
set(CXXFLAGS "")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lpthread -lopenal -lboost_serialization -lgtest")

#Looking for source files
include_directories(include)

if (DEBUG)
	add_compile_definitions(DEBUG)
	file(GLOB SOURCES "src/*.cpp" "tests/*.cpp")
 
else()
	file(GLOB SOURCES "src/*.cpp")

endif()

#Command to compile the whole project
add_executable(chip8 ${SOURCES})