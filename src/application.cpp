/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include "application.hpp"

using application::exceptions::InvalidFileException;
using application::hw::CPU;

namespace application {
	Application::Application(std::string filename) :
		cpu_{std::make_unique<CPU>()} {
		set_file(filename);
	}

	void Application::start() {
		// Load the file
		this->load();

		// Start the main cycle
		cpu_->start();
	}

	void Application::set_file(const std::string& value) {
		if (value.empty())
			throw InvalidFileException(value); 

		filename_ = value;
	}

	void Application::load() {
		auto ram{cpu_->ram()};
		auto offset{constants::ram::offset};
		std::ifstream stream{filename_, std::ios::binary};
		char byte{0};

		// Throw an exception if the file was not opened
		if (!stream.is_open()) 
			throw std::runtime_error("Could not open file");

		// TODO : handle an empty file
		// TODO : handle incorrect offset

		//Write the program into the memory while it's not the end of the file
		while (!stream.eof()) {
			// Read exactly ONE byte from the file
			stream.read(&byte, 1);

			// Write a byte from the stream
			ram->at(offset) = byte;

			// Move the offset
			++offset;
		}

		// Close the file
		stream.close();
	}

	const std::string& Application::get_file() const noexcept {
		return filename_;
	}
}