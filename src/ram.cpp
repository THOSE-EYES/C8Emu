#include "ram.hpp"

RAM::RAM() {
	// The size can't be less than 1
	if (constants::memory::SIZE < 1) 
		new std::invalid_argument("Size of memory is incorrect");

	_memory = std::unique_ptr<std::deque<uint8_t>>(new std::deque<uint8_t>());		
	_cell = _memory->begin();
}

RAM::~RAM() {}

void RAM::write(uint8_t data) {
	//Write data
	*_cell = data;
}

uint8_t RAM::read() {
	//Read a block
	uint8_t data = *_cell;

	//Return data
	return data;
}

void RAM::move(unsigned short block) {
	//Check if block number is out range of the memory and raise an exception if it is
	if(block >= constants::memory::SIZE) 
		throw new std::invalid_argument("Desired block is out of range");

	//Move the pointer to the block
	_cell = _memory->begin() + block;
}

unsigned short RAM::getAdress(void) const {
	return std::distance(_memory->begin(), _cell);;
}

void RAM::load(const std::string filename, unsigned short offset) {
	std::fstream stream(filename, std::ios::in | std::ios::binary);     // Stream to read the specified file
    char byte;                                                 			// Temporary variable for storing read bytes

    // Throw an exception if the file was not opened
	if (!stream.is_open()) 
		throw new std::runtime_error("Could not open file");

    // TODO : Handle an empty file

	//Write the program into the memory while it's not the end of the file
	while (!stream.eof()) {
        // Move the pointer to the right place in the memory
	    move(offset);
        
        // Read exactly ONE byte from the file
        stream.read(&byte, 1);

        // Write a byte from the stream
		write(byte);

        // Move the offset
        ++offset;
	}
}