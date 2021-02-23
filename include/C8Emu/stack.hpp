#pragma once

#include <stdexcept>
#include <memory>
#include <deque>

#include "global.hpp"

class Stack final {
private:
	std::unique_ptr<std::deque<unsigned short>> _stack;				// Array of the stack

public:
    /*
     * Constructor
     */
    Stack();

    /*
     * Destructor
     */
    ~Stack();

    /*
     * Storing an adress of return inside of the stack (used when a subroutine is called)
     * @param ram_adress - adress in the memory to store
     */
	void store(unsigned short);

    /*
     * Return the last element and delete it from the stack
     * @return - the last added element
     */
	unsigned short remove(void);
};
