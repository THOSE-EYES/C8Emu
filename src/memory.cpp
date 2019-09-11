#include "memory.h"

Memory::Memory() {
	//Initialize variables
	adress = 0x00;
	stack_adress = 0x00;
}

Memory::~Memory() {

}

void Memory::write_byte(unsigned char data) {
	//Write data
	memory[adress] = data;

	//Move the pointer
	move(adress++);
}

unsigned char Memory::read_byte() {
	//Read a block
	unsigned char data = memory[adress];

	//Move the pointer
	move(adress++);

	//Return data
	return data;
}

void Memory::move(unsigned short block) {
	//Check if block number is out range of the memory 
	if(block >= MEM_SIZE | block < 0) {
		//Raise an exception
		throw Exception(MEMRANGEOUTERR);
	}

	//Move the pointer to the block
	adress = block;
}

void Memory::nextBlock(unsigned char interval) {
	//Call the function "move" with incremented adress
	move(adress++);
}

void Memory::storeReturnAdress() {
	//Check if the stack is full
	if (stack_adress == STACK_SIZE) {
		//Raise an exception
		throw Exception();
	}

	//Store the adress in the stack
	stack[stack_adress] = adress;

	//Move the adress to a free block
	stack_adress++;
}

void Memory::recurr() {
	//Check if the stack is empty
	if ((stack_adress == 0) & (stack[stack_adress] != 0x0)) {
		//Raise an exception
		throw Exception();
	}

	//Recovering the previous adress of memory to continue executing the previous task
	adress = stack[stack_adress];

	//Clearing the element
	stack[stack_adress] = 0x0;

	//Moving to the next stack block
	stack_adress--;
}