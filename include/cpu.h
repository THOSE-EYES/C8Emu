/*
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"); you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
*/

#pragma once

#include <climits>
#include <experimental/random>

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