#include "ram.hpp"

RAM::RAM(unsigned short size) {
	// The size can't be less than 1
	if (size < 1) throw Exception(SMALLMEMSZERR);

	_memory = new unsigned char[size];		// The array to store data
	_size = size;							// Total size of the allocated memory
	_adress = 0;							// Current unused adress in the memory
}

RAM::~RAM() {
	delete _memory;
}

void RAM::write(unsigned char data) {
	//Write data
	_memory[_adress] = data;
}

unsigned char RAM::read() {
	//Read a block
	unsigned char data = _memory[_adress];

	//Return data
	return data;
}

void RAM::move(unsigned short block) {
	//Check if block number is out range of the memory and raise an exception if it is
	if((block >= _size) || (block < 0)) throw Exception(MEMRANGEOUTERR);

	//Move the pointer to the block
	_adress = block;
}

unsigned short RAM::getAdress(void) const {
	return _adress;
}

void RAM::load(const std::string filename, int offset) {
	std::fstream stream(filename, std::ios::in | std::ios::binary);     // Stream to read the specified file
    char byte;                                                 			// Temporary variable for storing read bytes

    // Throw an exception if the file was not opened
	if (!stream.is_open()) throw Exception(FOPENERR);

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