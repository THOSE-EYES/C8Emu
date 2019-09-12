#include "cpu.h"

CPU::CPU(Memory* filled_memory, AbstractPlayer* selected_api) {
	//Initializing all the variables
	memory = filled_memory;

	player = selected_api;
}

CPU::~CPU() {

}

void CPU::emulateCycle() {
	//Declare and/or initialize variables
	static unsigned short opcode;

	//Call essential functions(e.g. moving memory pointer to the needed position)
	try {
		memory->move(OFFSET);
	}
	catch (Exception exception) {
		//Do a specific task
	}

	//Create a game cycle
	while(isRunning) {
		//Check if the opcode must be skipped
		if(!isSkipping) {
			//Set or clear the opcode variable
			opcode = 0x00;

			//Fetch opcode
			opcode = (memory->read_byte() << 8);
			memory->nextBlock();
			opcode |= memory->read_byte();

			//Move to the next block of memory (for future)
			memory->nextBlock();

			//Pass the opcode and catch exceptions
			try {
				execute(opcode);
			}
			catch (Exception exception) {
				switch (exception.code()) {
					case OPCODEERR:
						//Do a specific task

						break;
				}
			}

			//Check for interrupts
			checkInterrupts();
		}
		else {
			memory->nextBlock(2);
		}
	}
}

void CPU::execute(unsigned short opcode) {
	//Execute the opcode
	switch((opcode & 0xF000) >> 12) {
		case 0x0:
			//0NNN - Calls RCA 1802 program at address NNN. Not necessary for most ROMs

			break;

		case 0x1:
			//1NNN - Jumps to address NNN
			memory->move(opcode & 0x0FFF); //Clearing the first 4 bits to get an adress

			break;

		case 0x2:
			//2NNN - Calls subroutine at NNN
			memory->storeReturnAdress();
			memory->move(opcode & 0x0FFF);

		break;

		case 0x3:
			//3XNN - Skips the next instruction if VX equals NN
			if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
				isSkipping = true;
			}

			break;

		case 0x4:
			//4XNN - Skips the next instruction if VX doesn't equal NN
			if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
				isSkipping = true;
			}

			break;

		case 0x5:
			//5XY0 - Skips the next instruction if VX equals VY
			if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
				isSkipping = true;
			}

			break;

		case 0x6:
			//6XNN - Sets VX to NN
			V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);

			break;

		case 0x7:
			//7XNN - Adds NN to VX (carry flag is not changed)
			V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);

			break;

		case 0x8:
			switch (opcode & 0xF) {
				case 0:
					//8XY0 - Sets VX to the value of VY
					V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4];

					break;

				case 1:
					//8XY1 - Sets VX to VX or VY (bitwise OR operation)
					V[(opcode & 0x0F00) >> 8] |= V[(opcode & 0x00F0) >> 4];

					break;

				case 2:
					//8XY2 - Sets VX to VX and VY (bitwise AND operation)
					V[(opcode & 0x0F00) >> 8] &= V[(opcode & 0x00F0) >> 4];

					break;

				case 3:
					//8XY3 - Sets VX to VX xor VY
					V[(opcode & 0x0F00) >> 8] ^= V[(opcode & 0x00F0) >> 4];

					break;

				case 4:
					//8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't

					//Check if CF(carry flag) must be set
					if((V[(opcode & 0x0F00) >> 8] + V[(opcode & 0x00F0) >> 4]) > UCHAR_MAX) {
						V[0xF] = 1;	//VF as a carry flag
					} 

					V[(opcode & 0x0F00) >> 8] += V[(opcode & 0x00F0) >> 4];

					break;

				case 5:
					//8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't

					//Check if BF(borrow flag) must be set
					if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
						V[0xF] = 1;
					}
					else if (V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0) >> 4]){
						V[0xF] = 0;
					}

					V[(opcode & 0x0F00) >> 8] -= V[(opcode & 0x00F0) >> 4];

					break;

				case 6:
					//8XY6 - Stores the least significant bit of VX in VF and then shifts VX to the right by 1
					V[0xF] = V[(opcode & 0x0F00) >> 8] & 0x1;

					V[(opcode & 0x0F00) >> 8] >>= 1;

					break;

				case 7:
					//8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
						
					//Check if BF(borrow flag) must be set
					if (V[(opcode & 0x0F00) >> 8] > V[(opcode & 0x00F0) >> 4]) {
						V[0xF] = 0;
					}
					else if (V[(opcode & 0x0F00) >> 8] < V[(opcode & 0x00F0) >> 4]){
						V[0xF] = 1;
					}

					V[(opcode & 0x0F00) >> 8] = V[(opcode & 0x00F0) >> 4] - V[(opcode & 0x0F00) >> 8];

					break;

				case 0xE: 
					//8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1
					V[0xF] = (V[(opcode & 0x0F00) >> 8] >> 7) & 0x1;

					V[(opcode & 0x0F00) >> 8] <<= 1;

					break;
			}

			break;

		case 0x9:
			//9XY0 - Skips the next instruction if VX doesn't equal VY
			if (V[(opcode & 0x0F00) >> 8] != V[(opcode & 0x00F0) >> 4]) {
				isSkipping = true;
			}

			break;

		case 0xA:
			//ANNN - Sets I to the address NNN
			VI = opcode & 0x0FFF;

			break;

		case 0xB:
			//BNNN - Jumps to the address NNN plus V0
			memory->move((opcode & 0x0FFF) + V[0]);

			break;

		case 0xC:
			//CXNN - Sets VX to the result of a bitwise and operation on a random number \
			(typically: 0 to 255) and NN
			V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF) & std::experimental::randint(0, 255);

			break;

		case 0xD:
			//DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels \
			and a height of N pixels. Each row of 8 pixels is read as bit-coded starting \
			from memory location I; I value doesn’t change after the execution of this \
			instruction. As described above, VF is set to 1 if any screen pixels are \
			flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t \
			happen

			break;

		case 0xE:
			switch(opcode & 0xFF) {
				case 0x9E:
					//EX9E - Skips the next instruction if the key stored in VX is pressed

					break;

				case 0xA1:
					//EXA1 - Skips the next instruction if the key stored in VX isn't pressed

					break;
				}

				break;

		case 0xF:
			switch(opcode & 0xFF) {
				case 0x07:
					//FX07 - Sets VX to the value of the delay timer
					V[opcode & 0x0F00] = DT;

					break;

				case 0x0A:
					//FX0A - A key press is awaited, and then stored in VX
						
					/*
					while() {

					}
					*/

					break;

				case 0x15:
					//FX15 - Sets the delay timer to VX
					DT = V[opcode & 0x0F00];

					break;

				case 0x18:
					//FX18 - Sets the sound timer to VX
					ST = V[opcode & 0x0F00];

					//Triggering the buzzer using a thread
					player->playBuzzer();

					break;

				case 0x1E:
					//FX1E - Adds VX to I
					VI += V[opcode & 0x0F00];

					break;

				case 0x29:
					//FX29 - Sets I to the location of the sprite for the character \
					in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font

					break;

				case 0x33:
					//FX33 - Stores the binary-coded decimal representation of VX, with \
					the most significant of three digits at the address in I, the middle \
					digit at I plus 1, and the least significant digit at I plus 2

					break;

				case 0x55:
					//FX55 - Stores V0 to VX (including VX) in memory starting at address I. \
					The offset from I is increased by 1 for each value written, but I itself \
					is left unmodified

					memory->storeReturnAdress();

					memory->move(VI);

					for (int counter = 0; counter != REGISTERS_AMOUNT; counter++) {
						memory->write_byte(V[counter]);
						memory->nextBlock();
					}

					memory->recurr();
						
					break;

				case 0x65:
					//FX65 - Fills V0 to VX (including VX) with values from memory starting at \
					address I. The offset from I is increased by 1 for each value written, but \
					I itself is left unmodified
						
					memory->storeReturnAdress();

					memory->move(VI);

					for (int counter = 0; counter != REGISTERS_AMOUNT; counter++) {
						V[counter] = memory->read_byte();
						memory->nextBlock();
					}

					memory->recurr();

					break;
			}

			break;

		default :
			switch(opcode) {
				case 0x00EE:
					//Exit from a subroutine
					memory->recurr();

					break;

				case 0x00E0:
					//Clear the screen
					//display->clear();

					break;

				default:
					throw Exception(OPCODEERR);

			}		
	}
}

void CPU::checkInterrupts() {
	//Check the delay timer
	if(DT == 0) {

	}
	
	//Check the sound timer
	if (ST == 0) {
		player->stop();
	}
}