#include "memory.h"

Memory::Memory() {
	//Initialize variables
	this->adress = 0x00;
	this->stack_adress = 0x00;
}

Memory::~Memory() {

}

void Memory::write(unsigned char data) {
	//Check if block number is bigger than memory size

	//Write data
	memory[adress] = data;

	//Move the pointer
	this->adress++;
}

unsigned char Memory::read() {
	//Check if block number is bigger than memory size

	//Read a block
	unsigned char data = memory[adress];

	//Move the pointer
	this->adress++;

	//Return data
	return data;
}

void Memory::move(unsigned short block) {
	//Check if block number is bigger than memory size
	if(block >= MEM_SIZE | block < 0) {
		//Raise an exception
	}

	//Move the pointer to the block
	this->adress = block;
}

void Memory::storeReturnAdress() {
	//Store the adress in the stack
	this->stack[stack_adress] = adress;

	//Move the adress to a free block
	this->stack_adress++;
}

void Memory::recurr() {

}