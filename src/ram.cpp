#include "ram.h"

RAM::RAM(unsigned short size) {
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

unsigned short RAM::getAdress(void) {
	return _adress;
}