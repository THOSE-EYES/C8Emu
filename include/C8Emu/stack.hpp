#pragma once

#include <stdexcept>
#include <memory>

class Stack final {
private:
	std::unique_ptr<unsigned short[]> _stack;				// Array of the stack
    unsigned int _size;             						// Size of the stack
	unsigned short _adress;        							// Current block of the stack

public:
    /*
     * Constructor
     * @param size - size of the stack in bytes
     */
    Stack(int);

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
