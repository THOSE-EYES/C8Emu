#pragma once

#include "memory.h"
#include "graphics.h"
#include "input.h"
#include "loader.h"
#include "sound.h"

class CPU final{
private:
	//Registers
	unsigned char V[16];	//General purpose registers
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
	void setDTimer(unsigned char timer_value);	//Setting the delay timer
	void setSTimer(unsigned char timer_value);	//Setting the sound timer
};