cmake_minimum_required(VERSION 3.15)
project(CHIP-8)

#Setting the compiler
set(CMAKE_CXX_COMPILER "g++")
set(CXXFLAGS "")
set(CMAKE_CXX_STANDARD_LIBRARIES "-lpthread -lopenal -lboost_serialization")

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(chip8 ${SOURCES})