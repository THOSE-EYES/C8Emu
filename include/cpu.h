#pragma once

//C or C++ Library
#include <climits>
#include <experimental/random>

//Headers written by me
#include "memory.h"
#include "graphics.h"
#include "io.h"
#include "keyboard.h"
#include "sound.h"
#include "exceptions.h"

#define REGISTERS_AMOUNT 16

class CPU final{
private :
	//Registers
	unsigned char V[REGISTERS_AMOUNT];	//General purpose registers
	unsigned short VI;	//Index register

	//Timers
	unsigned char DT;	//Delay timer
	unsigned char ST;	//Sound timer

	//Flags
	bool isRunning = false;
	bool isSkipping = false;

	//Instances
	Memory* memory;
	AbstractPlayer* player;

public :
	CPU(Memory*, AbstractPlayer* = NULL);
	~CPU();

	void emulateCycle();
	void execute(unsigned short);	//Executing an opcode which is stored in a Memory instance
	void checkInterrupts();
};