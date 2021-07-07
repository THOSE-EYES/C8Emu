# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
# 
#  http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.

# Setting CMake
cmake_minimum_required(VERSION 3.15)
project(C8Emu)
option(TESTING "Build unit tests along with the project" OFF)

# Setting the compiler for Windows
if (WIN32)
	# FIXME : To do
	#set(CXXFLAGS "")
	#set(CMAKE_CXX_STANDARD_LIBRARIES "-lopenal -lboost_serialization -lgtest")
endif (WIN32)

# Setting the compiler for Linux
if (UNIX)
	set(CMAKE_CXX_COMPILER "g++")
	set(CXXFLAGS "-O2")
	set(CMAKE_CXX_STANDARD_LIBRARIES "-lpthread -lopenal -lboost_serialization -lgtest -lgmock -lGL -lGLU -lglut")
endif (UNIX)

# Looking for source files
include_directories(include)

# Find the files of the project
if (TESTING)
	# Include additional headers
	include_directories(tests)

	# Add TESTING definition into the project
	add_compile_definitions(TESTING)

	# Find source files
	file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp" "tests/*.cpp")
else()
	# Find source files
	file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")
endif()

# Command to compile the whole project
add_executable(${PROJECT_NAME} ${SOURCES})