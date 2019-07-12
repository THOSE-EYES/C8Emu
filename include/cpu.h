#pragma once

#include <climits>
#include <experimental/random>

#include "memory.h"
#include "graphics.h"
#include "input.h"
#include "loader.h"
#include "sound.h"

#define REGISTERs_AMOUNT 16

class CPU final{
private:
	//Registers
	unsigned char V[REGISTERs_AMOUNT];	//General purpose registers
	unsigned short VI;	//Index register

	//Timers
	unsigned char DT;	//Delay timer
	unsigned char ST;	//Sound timer

	//Flags
	bool isRunning = false;
	bool isSkipping = false;

	//Instances
	Memory* memory

public:
	CPU();
	~CPU();

	void emulateCycle();
	void execute(unsigned short opcode);	//Executing an opcode which is stored in a Memory instance
	void checkInterrupts();
};