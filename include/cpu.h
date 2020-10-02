#pragma once

#include <climits>
#include <experimental/random>

#include "ram.h"
#include "stack.h"
#include "graphics.h"
#include "keyboard.h"
#include "exceptions.h"
#include "global.h"

class CPU final {
private :
	unsigned char _registers[REGISTERS_AMOUNT];		// General purpose registers
	unsigned short _index_register;					// Index register
	unsigned char _d_timer;							// Delay timer
//	unsigned char _s_timer;							// Sound timer
	bool _isRunning = false;						// Flag of execution
	bool _isSkipping = false;						// Flag of the next opcode to be skipped
	RAM* _memory;									// Instance of virtual memory
	Stack* _stack;

	/**
	 * Executing opcodes, specific for the CHIP-8 interpretator
	 * @param opcode - data to process
	 */
	void execute(const unsigned short);		//Executing an opcode which is stored in a Memory instance

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