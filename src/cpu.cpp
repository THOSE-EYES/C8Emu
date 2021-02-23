#include "cpu.hpp"

CPU::CPU(RAM* ram, Stack* stack) {
	// Throw an exception if one of the pointer is nullptr
	if( (ram == nullptr) || (stack == nullptr))
		throw new std::invalid_argument("Memory is nullptr");

	ram_ = std::unique_ptr<RAM>(ram);			// Filled array of opcodes
	stack_ = std::unique_ptr<Stack>(stack);		// Stack
	registers_ = std::unique_ptr<std::deque<uint8_t>>(new std::deque<uint8_t>());
}

CPU::~CPU() {}

void CPU::start(void) {
	// Declare and/or initialize variables
	uint16_t opcode,							// Storing the current opcode
		offset = constants::memory::OFFSET;		// Current position in the memory
	isRunning_ = true;							// Indicator of execution

	// Start the execution
	while(isRunning_) {
		//Check if the opcode must be skipped (skip if yes)
		if(isSkipping_) offset += 2;

		//Set or clear the opcode variable
		opcode = 0x00;
		
		//Fetch opcode (using loop to obtain two bytes from the memory)
		for (uint8_t opcode_offset = 0; opcode_offset < 2; ++opcode_offset) {
			// Move the memory index to a desired position
			ram_->move(offset);

			// Fetch a part of opcode
			opcode |= (ram_->read() << (1 - opcode_offset) * 8);

			// Move the offset
			++offset;
		}

		//Pass the opcode
		execute(opcode);

		// Update the offset if it was changed by opcode
		if (offset != ram_->getAdress() + 1)
			offset = ram_->getAdress();

		// Check for interrupts
		checkInterrupts();
	}
}

void CPU::execute(const uint16_t opcode) {
	//Execute the opcode
	switch((opcode & 0xF000) >> 12) {
		case 0x0:
			switch(opcode) {
				case 0x0000:
					isRunning_ = false;

					break;

				case 0x00EE:
					//Exit from a subroutine
					ram_->move(stack_->remove());

					break;

				case 0x00E0:
					//Clear the screen
					//display->clear();

					break;

				//0NNN - Calls RCA 1802 program at address NNN. Not necessary for most ROMs
				default:
					
					break;
			}

			break;

		case 0x1:
			//1NNN - Jumps to address NNN
			ram_->move(opcode & 0x0FFF); //Clearing the first 4 bits to get an adress

			break;

		case 0x2:
			//2NNN - Calls subroutine at NNN
			stack_->store(ram_->getAdress());
			ram_->move(opcode & 0x0FFF);

			break;

		case 0x3:
			//3XNN - Skips the next instruction if VX equals NN
			if (registers_->at((opcode & 0x0F00) >> 8) == (opcode & 0x00FF)) isSkipping_ = true;

			break;

		case 0x4:
			//4XNN - Skips the next instruction if VX doesn't equal NN
			if (registers_->at((opcode & 0x0F00) >> 8) != (opcode & 0x00FF)) isSkipping_ = true;

			break;

		case 0x5:
			//5XY0 - Skips the next instruction if VX equals VY
			if (registers_->at((opcode & 0x0F00) >> 8) == registers_->at((opcode & 0x00F0) >> 4)) isSkipping_ = true;

			break;

		case 0x6:
			//6XNN - Sets VX to NN
			registers_->at((opcode & 0x0F00) >> 8) = (opcode & 0x00FF);

			break;

		case 0x7:
			//7XNN - Adds NN to VX (carry flag is not changed)
			registers_->at((opcode & 0x0F00) >> 8) += (opcode & 0x00FF);

			break;

		case 0x8:
			switch (opcode & 0xF) {
				case 0:
					//8XY0 - Sets VX to the value of VY
					registers_->at((opcode & 0x0F00) >> 8) = registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 1:
					//8XY1 - Sets VX to VX or VY (bitwise OR operation)
					registers_->at((opcode & 0x0F00) >> 8) |= registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 2:
					//8XY2 - Sets VX to VX and VY (bitwise AND operation)
					registers_->at((opcode & 0x0F00) >> 8) &= registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 3:
					//8XY3 - Sets VX to VX xor VY
					registers_->at((opcode & 0x0F00) >> 8) ^= registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 4:
					//8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't

					//Check if CF(carry flag) must be set
					if((registers_->at((opcode & 0x0F00) >> 8) + registers_->at((opcode & 0x00F0) >> 4)) > UCHAR_MAX) registers_->at(0xF) = 1;	//VF as a carry flag
					
					registers_->at((opcode & 0x0F00) >> 8) += registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 5:
					//8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't

					//Check if BF(borrow flag) must be set
					if (registers_->at((opcode & 0x0F00) >> 8) > registers_->at((opcode & 0x00F0) >> 4)) registers_->at(0xF) = 1;
					else if (registers_->at((opcode & 0x0F00) >> 8) < registers_->at((opcode & 0x00F0) >> 4)) registers_->at(0xF) = 0;

					registers_->at((opcode & 0x0F00) >> 8) -= registers_->at((opcode & 0x00F0) >> 4);

					break;

				case 6:
					//8XY6 - Stores the least significant bit of VX in VF and then shifts VX to the right by 1
					registers_->at(0xF) = registers_->at((opcode & 0x0F00) >> 8) & 0x1;
					registers_->at((opcode & 0x0F00) >> 8) >>= 1;

					break;

				case 7:
					//8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't
						
					//Check if BF(borrow flag) must be set
					if (registers_->at((opcode & 0x0F00) >> 8) > registers_->at((opcode & 0x00F0) >> 4)) registers_->at(0xF) = 0;
					else if (registers_->at((opcode & 0x0F00) >> 8) < registers_->at((opcode & 0x00F0) >> 4)) registers_->at(0xF) = 1;

					registers_->at((opcode & 0x0F00) >> 8) = registers_->at((opcode & 0x00F0) >> 4) - registers_->at((opcode & 0x0F00) >> 8);

					break;

				case 0xE: 
					//8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1
					registers_->at(0xF) = (registers_->at((opcode & 0x0F00) >> 8) >> 7) & 0x1;

					registers_->at((opcode & 0x0F00) >> 8) <<= 1;

					break;
			}

			break;

		case 0x9:
			//9XY0 - Skips the next instruction if VX doesn't equal VY
			if (registers_->at((opcode & 0x0F00) >> 8) != registers_->at((opcode & 0x00F0) >> 4)) isSkipping_ = true;

			break;

		case 0xA:
			//ANNN - Sets I to the address NNN
			index_register_ = opcode & 0x0FFF;

			break;

		case 0xB:
			//BNNN - Jumps to the address NNN plus V0
			ram_->move((opcode & 0x0FFF) + registers_->at(0));

			break;

		case 0xC:
			//CXNN - Sets VX to the result of a bitwise and operation on a random number \
			(typically: 0 to 255) and NN
			registers_->at((opcode & 0x0F00) >> 8) = (opcode & 0x00FF) & std::experimental::randint(0, 255);

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
					registers_->at(opcode & 0x0F00) = delay_timer_;

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
					delay_timer_ = registers_->at(opcode & 0x0F00);

					break;

				case 0x18:
					//FX18 - Sets the sound timer to VX
					//sound_timer_ = registers_->at(opcode & 0x0F00);

					//Triggering the buzzer using a thread
					//player->playBuzzer();

					break;

				case 0x1E:
					//FX1E - Adds VX to I
					index_register_ += registers_->at(opcode & 0x0F00);

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

					stack_->store(ram_->getAdress());

					ram_->move(index_register_);

					for (uint8_t offset = 0; offset != constants::cpu::REG; offset++) {
						ram_->write(registers_->at(offset));
						ram_->move(index_register_ + offset);
					}

					ram_->move(stack_->remove());
						
					break;

				case 0x65:
					//FX65 - Fills V0 to VX (including VX) with values from memory starting at \
					address I. The offset from I is increased by 1 for each value written, but \
					I itself is left unmodified
						
					stack_->store(ram_->getAdress());

					ram_->move(index_register_);

					for (uint8_t offset = 0; offset != constants::cpu::REG; offset++) {
						registers_->at(offset) = ram_->read();
						ram_->move(index_register_ + offset);
					}

					ram_->move(stack_->remove());

					break;
			}

			break;

		default :
			throw new std::invalid_argument("Opcode is invalid");
	}
}

void CPU::checkInterrupts(void) noexcept {
	//Check the delay timer
	if(delay_timer_ == 0) {

	}
	
	//Check the sound timer
	//if (sound_timer_ == 0) player->stop();
}