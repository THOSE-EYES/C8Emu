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