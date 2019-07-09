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

/* CHIP-8 MEMORY MAP

+---------------+= 0xFFF (4095) End of Chip-8 RAM
|               |
|               |
|               |
|               |
|               |
| 0x200 to 0xFFF|
|     Chip-8    |
| Program / Data|
|     Space     |
|               |
|               |
|               |
+- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
|               |
|               |
|               |
+---------------+= 0x200 (512) Start of most Chip-8 programs
| 0x000 to 0x1FF|
| Reserved for  |
|  interpreter  |
+---------------+= 0x000 (0) Start of Chip-8 RAM

*/

#pragma once

#define OFFSET 0x200
#define MEM_SIZE 4096
#define STACK_SIZE 16

class Memory final{
private:
	unsigned char memory[MEM_SIZE];
	unsigned short adress;	//Current block of the memory

	unsigned short stack[STACK_SIZE];
	unsigned short stack_adress;	//Current block of the stack

public:
	Memory();
	~Memory();

	void write(unsigned char data);	//Writing data to the memory array consistently
	unsigned char read();	//Reading data from the memory array consistently
	void move(unsigned short block);	//Moving the pointer to a block

	void storeReturnAdress();	//Used when a subroutine is called to go back later (RENAME)
	void recurr();	//Returning to a previous task(after completing a subroutine)
};