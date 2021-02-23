#include "stack.hpp"

Stack::Stack() {
	// Throw an exception if the size is less than 1
	if (constants::stack::SIZE < 1)
		throw new std::invalid_argument("Size of memory is incorrect");

	_stack = std::unique_ptr<std::deque<unsigned short>>(new std::deque<unsigned short>());
}

Stack::~Stack() {}

void Stack::store(unsigned short ram_adress) {
	//Check if the stack is full and raise an exception if it is
	if (_stack->size() == (constants::stack::SIZE - 1))
		throw new std::runtime_error("Stack is full");

	//Store the adress in the stack
	_stack->push_back(ram_adress);
}

unsigned short Stack::remove(void) {
    unsigned short ram_adress;      // Used as a result (return the last item from the stack and delete it)

	//Check if the stack is empty and raise an exception if it is
	if (_stack->empty()) 
		throw new std::runtime_error("Stack is empty");

	//Recovering the previous adress of memory to continue executing the previous task
	ram_adress = _stack->back();

	//Clearing the element
	_stack->pop_back();

    return ram_adress;
}