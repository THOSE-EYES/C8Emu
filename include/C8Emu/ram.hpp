#pragma once

#include "exceptions.hpp"
#include <fstream>

class RAM final {
private :
	unsigned char* _memory;		// Array of values stored inside of the memory
	unsigned short _size,		// The size of the used memory
					_adress;		// Current block of the memory

public :
	/**
	 * Constructor of virtual RAM memory for emulation
	 * @param size - size of memory to allocate
	 */
	RAM(unsigned short);

	/**
	 * Destructor
	 */
	~RAM();

	/**
	 * Write one byte to the memory (after updating the index)
	 * @param data - byte to store inside of the memory
	 */
	void write(unsigned char);

	/**
	 * Read only one byte from the memory (after updating the index)
	 * @return - a read byte from the memory
	 */
	unsigned char read();

	/**
	 * Moving the pointer to a certain block of data
	 * @param block - index of block inside of the memory
	 */
	void move(unsigned short);

	/**
	 * Get current index of block inside the memory
	 * @return - block index
	 */
	unsigned short getAdress(void) const ;

    /**
     * Loading a file into the specified memory
     * @param filename - name of the file to be loaded
     * @param offset offset in the memory
     */
    void load(const std::string, int);
};