#Setting CMake
cmake_minimum_required(VERSION 3.15)
project(C8Emu)
option(TESTING "Build unit tests along with the project" OFF)

# Setting the compiler for Windows
if (WIN32)
	#set(CXXFLAGS "")
	#set(CMAKE_CXX_STANDARD_LIBRARIES "-lopenal -lboost_serialization -lgtest")
endif (WIN32)

# Setting the compiler for Linux
if (UNIX)
	set(CMAKE_CXX_COMPILER "g++")
	set(CXXFLAGS "")
	set(CMAKE_CXX_STANDARD_LIBRARIES "-lpthread -lopenal -lboost_serialization -lgtest -lGL -lGLU -lglut")
endif (UNIX)

# Looking for source files
include_directories(include/C8Emu)

# Find the files of the project
if (TESTING)
	add_compile_definitions(TESTING)
	file(GLOB SOURCES "src/*.cpp" "tests/*.cpp")
else()
	file(GLOB SOURCES "src/*.cpp")
endif()

# Command to compile the whole project
add_executable(chip8 ${SOURCES})