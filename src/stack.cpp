#include "stack.h"

Stack::Stack(int size) {
    _size = size;                               // Size of the stack
    _stack = new unsigned short[size];          // New stack
    _adress = 0;                                // Current adress in the stack
}

Stack::~Stack() {
    // Deleting the stack at destruction
    delete[] _stack;
}

void Stack::store(unsigned short ram_adress) {
	//Check if the stack is full and raise an exception if it is
	if ((_adress == (_size - 1)) & (_stack[_adress] != 0x0)) throw Exception(STFULLERROR);

	//Store the adress in the stack
	_stack[_adress] = ram_adress;

	//Move the adress to the next free block if it's not the end of stack
	if ((_adress != (_size - 1))) _adress++;
} 

unsigned short Stack::remove(void) {
    unsigned short ram_adress;      // Used as a result (return the last item from the stack and delete it)

	//Check if the stack is empty and raise an exception if it is
	if ((_adress == 0) & (_stack[_adress] == 0)) throw Exception(STEMPTYERROR);

	//Moving to the previous stack block
	if (_adress != 0) _adress--;

	//Recovering the previous adress of memory to continue executing the previous task
	ram_adress = _stack[_adress];

	//Clearing the element
	_stack[_adress] = 0;

    return ram_adress;
}