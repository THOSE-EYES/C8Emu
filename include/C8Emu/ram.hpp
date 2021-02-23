#pragma once

#include <fstream>
#include <memory>
#include <deque>
#include <iterator>

#include "global.hpp"

class RAM final {
private :
	std::unique_ptr<std::deque<uint8_t>> _memory;
	std::deque<uint8_t>::iterator _cell;

public :
	/**
	 * Constructor of virtual RAM memory for emulation
	 * @param size - size of memory to allocate
	 */
	RAM();

	/**
	 * Destructor
	 */
	~RAM();

	/**
	 * Write one byte to the memory (after updating the index)
	 * @param data - byte to store inside of the memory
	 */
	void write(uint8_t);

	/**
	 * Read only one byte from the memory (after updating the index)
	 * @return - a read byte from the memory
	 */
	uint8_t read();

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
    void load(const std::string, unsigned short);
};