#include "cpu.h"

CPU::CPU() {
}

CPU::~CPU() {

}

void CPU::emulateCycle() {
	//Initialize variables
	static unsigned short opcode = 0x00;

	//Call essential functions(e.g. moving memory pointer to the needed position)
	memory->move(0x200);

	//Create a game cycle
	while(isRunning) {
		//Check if the opcode must be skipped
		if(!isSkipping) {
			//Fetch opcode
			opcode = (memory->read() << 8) | (memory->read());

			//Pass the opcode
			execute(opcode);

			//Check for interrupts
			checkInterrupts();
		}
	}
}

void CPU::execute(unsigned short opcode) {
	//Create variables
	bool isExecuted = true;

	//Execute the opcode
	switch(opcode) {	//Execute some simple commands without any argument
		case 00EE:
			//Exit from a subroutine

			break;

		case 00E0:
			//Clear the screen
			//display->clear();

			break;

		default:
			isExecuted = false;
			break;
	}

	if(isExecuted == false) {	//Execute other commands
		switch((opcode & 0xF000) >> 12) {
			case 0:
				//0NNN - Calls RCA 1802 program at address NNN. Not necessary for most ROMs

				break;

			case 1:
				//1NNN - Jumps to address NNN
				memory->move(opcode & 0x0FFF); //Clearing the first 4 bits to get an adress

				break;

			case 2:
				//2NNN - Calls subroutine at NNN
				memory->storeReturnAdress();
				memory->move(opcode & 0x0FFF);

				break;

			case 3:
				//3XNN - Skips the next instruction if VX equals NN
				if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF)) {
					isSkipping = true;
				}

				break;

			case 4:
				//4XNN - Skips the next instruction if VX doesn't equal NN
				if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF)) {
					isSkipping = true;
				}

				break;

			case 5:
				//5XY0 - Skips the next instruction if VX equals VY
				if (V[(opcode & 0x0F00) >> 8] == V[(opcode & 0x00F0) >> 4]) {
					isSkipping = true;
				}

				break;

			case 6:
				//6XNN - Sets VX to NN
				V[(opcode & 0x0F00) >> 8] = (opcode & 0x00FF);

				break;

			case 7:
				//7XNN - Adds NN to VX (carry flag is not changed)
				V[(opcode & 0x0F00) >> 8] += (opcode & 0x00FF);

				break;

			case 8:
				switch (opcode & 0x000F) {
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

			case 9:
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
		}
	}
}

void CPU::checkInterrupts() {
	//Check the delay timer
	if(DT == 0) {

	}
	
	//Check the sound timer
	if (ST == 0) {

	}
}

void setDTimer(unsigned char timer_value) {
	DT = timer_value;
}

void setSTimer(unsigned char timer_value) {
	ST = timer_value;
}