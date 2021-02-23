#pragma once

#include <climits>
#include <experimental/random>
#include <deque>
#include <memory>

#include "ram.hpp"
#include "stack.hpp"
#include "graphics.hpp"
#include "keyboard.hpp"
#include "global.hpp"

class CPU {
protected :
	std::unique_ptr<std::deque<uint8_t>> registers_;
	uint16_t index_register_;					// Index register
	
	uint8_t delay_timer_;						// Delay timer
	uint8_t sound_timer_;							// Sound timer

	bool isRunning_ = false,						// Flag of execution
		isSkipping_ = false;						// Flag of the next opcode to be skipped

	std::unique_ptr<RAM> ram_;									// Instance of virtual memory
	std::unique_ptr<Stack> stack_;

	/**
	 * Executing opcodes, specific for the CHIP-8 interpretator
	 * @param opcode - data to process
	 */
	void execute(const uint16_t);		//Executing an opcode which is stored in a Memory instance

	/**
	 * Checking if there was an interrupt event
	 */
	void checkInterrupts(void) noexcept;

public :
	/**
	 * Constructor
	 * @param filled_memory - instance of RAM memory with a program in it
	 * @param stack - an instance of Stack
	 */
	CPU(RAM*, Stack*);

	/**
	 * Destructor
	 */
	~CPU();

	/**
	 * Statring to execute the main loop
	 */
	void start(void);
};