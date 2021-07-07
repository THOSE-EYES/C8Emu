#include "hw/cpu.hpp"

using application::exceptions::hw::cpu::InvalidOpcodeException;
using application::exceptions::hw::cpu::InvalidSubroutineException;
using application::hw::GPU;

namespace application {
	namespace hw {
		CPU::CPU() :
			gpu_{std::make_shared<GPU>()},
			ram_{std::make_shared<RAM>(constants::ram::size, 0)},
			stack_{std::make_unique<Stack>()},
			registers_{std::make_unique<GeneralRegisters>(
				constants::cpu::registers)} {

		}

		void CPU::start() {
			// Indicate the start of the execution
			flags_.running = true;

			// Start the execution
			for (;offset_ < constants::ram::size;
				offset_ += 2) {
				// If the execution is halted, exit the loop
				if (not flags_.running) break;

				// Execute the opcode
				Opcode opcode{(ram_->at(offset_ + 1) << 8) | 
					(ram_->at(offset_))};
				execute(opcode);

				// Check if there are interrupts
				interrupt();
			}
		}

		void CPU::execute(const Opcode& opcode) {
			// Get the most significant part of the opcode to process it
			switch ((opcode & 0xF000) >> 12) {
				// Process 0x0XXX opcodes
				case 0x0:
					switch(opcode) {
						case 0x0000:	_0000(); break;
						case 0x00EE: 	_00ee(); break;
						case 0x00E0: 	_00e0(); break;
						default: 		_0nnn(); break;
					}
					break;

				case 0x1: 	_1nnn(opcode); break;
				case 0x2:	_2nnn(opcode); break;
				case 0x3:	_3xnn(opcode); break;
				case 0x4:	_4xnn(opcode); break;
				case 0x5:	_5xy0(opcode); break;
				case 0x6:	_6xnn(opcode); break;
				case 0x7:	_7xnn(opcode); break;
				// Process 0x8XXX opcodes
				case 0x8:
					switch (opcode & 0xF) {
						case 0x0:	_8xy0(opcode); break;
						case 0x1:	_8xy1(opcode); break;
						case 0x2: 	_8xy2(opcode); break;
						case 0x3:	_8xy3(opcode); break;
						case 0x4:	_8xy4(opcode); break;
						case 0x5: 	_8xy5(opcode); break;
						case 0x6:	_8xy6(opcode); break;
						case 0x7:	_8xy7(opcode); break;
						case 0xE:	_8xye(opcode); break;
					}
					break;

				case 0x9: 	_9xy0(opcode); break;
				case 0xA:	_annn(opcode); break;
				case 0xB:	_bnnn(opcode); break;
				case 0xC:	_cxnn(opcode); break;
				case 0xD:	_dxyn(opcode); break;
				// Process 0xEXXX opcodes
				case 0xE:
					switch(opcode & 0xFF) {
						case 0x9E: _ex9e(opcode); break;
						case 0xA1: _exa1(opcode); break;
					}
					break;
				// Process 0xFXXX opcodes
				case 0xF:
					switch(opcode & 0xFF) {
						case 0x07:	_fx07(opcode); break;
						case 0x0A:	_fx0a(opcode); break;
						case 0x15:	_fx15(opcode); break;
						case 0x18:	_fx18(opcode); break;
						case 0x1E:	_fx1e(opcode); break;
						case 0x29:	_fx29(opcode); break;
						case 0x33:	_fx33(opcode); break;
						case 0x55:	_fx55(opcode); break;
						case 0x65:	_fx65(opcode); break;
					}
					break;

				default :
					throw InvalidOpcodeException(opcode);
			}
		}

		void CPU::interrupt() {
			//Check the delay timer
			if (timers_.delay == 0) {

			}
			
			//Check the sound timer
			if (timers_.sound == 0) {

			}
			
			// Decrement the timer values
			--timers_.delay;
			--timers_.sound;
		}

		void CPU::reset() {
			// Reset registers
			registers_.general->clear();
			registers_.index = 0;

			// Reset the timers
			timers_.delay = 0;
			timers_.sound = 0;
		}

		std::shared_ptr<CPU::RAM> CPU::ram() const noexcept {
			return ram_;
		}

		std::shared_ptr<application::hw::GPU> CPU::gpu() const noexcept {
			return gpu_;
		}

		void CPU::_0000() {
			flags_.running = false;
		}

		void CPU::_00ee() {
			if (stack_->empty()) 
				throw InvalidSubroutineException();

			offset_ = stack_->top();
			stack_->pop();
		}

		void CPU::_00e0() {
			// TODO
		}

		void CPU::_0nnn() {
			// noop
		}

		void CPU::_1nnn(const Opcode& value) {
			offset_ = (value & 0x0FFF);
		}

		void CPU::_2nnn(const Opcode& value) {
			stack_->push(offset_);
			offset_ = (value & 0x0FFF);
		}

		void CPU::_3xnn(const Opcode& value) {
			if (registers_.general->at((value & 0x0F00) >> 8) == 
				(value & 0x00FF)) 
				offset_ += 2;
		}

		void CPU::_4xnn(const Opcode& value) {
			if (registers_.general->at((value & 0x0F00) >> 8) != 
				(value & 0x00FF)) 
				offset_ += 2;
		}

		void CPU::_5xy0(const Opcode& value) {
			if (registers_.general->at((value & 0x0F00) >> 8) == 
				registers_.general->at((value & 0x00F0) >> 4)) 
				offset_ += 2;
		}

		void CPU::_6xnn(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) = 
				(value & 0x00FF);
		}

		void CPU::_7xnn(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) += 
				(value & 0x00FF);
		}

		void CPU::_8xy0(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) = 
				registers_.general->at((value & 0x00F0) >> 4);
		}

		void CPU::_8xy1(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) |= 
				registers_.general->at((value & 0x00F0) >> 4);
		}

		void CPU::_8xy2(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) &= 
				registers_.general->at((value & 0x00F0) >> 4);
		}

		void CPU::_8xy3(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) ^= 
				registers_.general->at((value & 0x00F0) >> 4);
		}

		void CPU::_8xy4(const Opcode& value) {
			// Check if CF(carry flag) must be set
			if((registers_.general->at((value & 0x0F00) >> 8) + 
				registers_.general->at((value & 0x00F0) >> 4)) > 
				std::numeric_limits<unsigned char>::max()) 
					registers_.general->at(0xF) = 1;	//VF as a carry flag

			//	Update VX
			registers_.general->at((value & 0x0F00) >> 8) += 
				registers_.general->at((value & 0x00F0) >> 4);
		}

		void CPU::_8xy5(const Opcode& value) {
			//Check if BF(borrow flag) must be set
			registers_.general->at(0xF) = 
				(registers_.general->at((value & 0x0F00) >> 8) > 
					registers_.general->at((value & 0x00F0) >> 4)) ? 1 : 0;

			// Update VX
			registers_.general->at((value & 0x0F00) >> 8) -= 
				registers_.general->at((value & 0x00F0) >> 4);

		}

		void CPU::_8xy6(const Opcode& value) {
			// Store LSB of VX into VF
			registers_.general->at(0xF) = 
				registers_.general->at((value & 0x0F00) >> 8) & 0x1;

			// Shift VX to the right
			registers_.general->at((value & 0x0F00) >> 8) >>= 1;
		}

		void CPU::_8xy7(const Opcode& value) {
			// Set VF to 1 if there's no borrow and to 0 otherwise
			if (registers_.general->at((value & 0x0F00) >> 8) > registers_.general->at((value & 0x00F0) >> 4)) registers_.general->at(0xF) = 0;
			else if (registers_.general->at((value & 0x0F00) >> 8) < registers_.general->at((value & 0x00F0) >> 4)) registers_.general->at(0xF) = 1;

			// Update VX
			registers_.general->at((value & 0x0F00) >> 8) = 
				registers_.general->at((value & 0x00F0) >> 4) - registers_.general->at((value & 0x0F00) >> 8);
		}
		
		void CPU::_8xye(const Opcode& value) {
			// Set VF to the MSB of VX
			registers_.general->at(0xF) = (registers_.general->at((value & 0x0F00) >> 8) >> 7) & 0x1;

			// Shift VX to the left
			registers_.general->at((value & 0x0F00) >> 8) <<= 1;
		}

		void CPU::_9xy0(const Opcode& value) {
			if (registers_.general->at((value & 0x0F00) >> 8) != 
				registers_.general->at((value & 0x00F0) >> 4)) 
					offset_ += 2;
		}

		void CPU::_annn(const Opcode& value) {
			registers_.index = value & 0x0FFF;
		}

		void CPU::_bnnn(const Opcode& value) {
			offset_ = ((value & 0x0FFF) + registers_.general->at(0));
		}

		void CPU::_cxnn(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) = 
				(value & 0x00FF) & std::experimental::randint(0, 255);
		}

		void CPU::_dxyn(const Opcode& value) {
			// TODO
		}

		void CPU::_ex9e(const Opcode& value) {
			// TODO
		}

		void CPU::_exa1(const Opcode& value) {
			// TODO
		}

		void CPU::_fx07(const Opcode& value) {
			registers_.general->at((value & 0x0F00) >> 8) = timers_.delay;
		}

		void CPU::_fx0a(const Opcode& value) {
			// TODO
			while (true) ;
		}

		void CPU::_fx15(const Opcode& value) {
			timers_.delay = registers_.general->at((value & 0x0F00) >> 8);
		}

		void CPU::_fx18(const Opcode& value) {
			timers_.sound = registers_.general->at((value & 0x0F00) >> 8);
		}

		void CPU::_fx1e(const Opcode& value) {
			registers_.index += registers_.general->at((value & 0x0F00) >> 8);
		}

		void CPU::_fx29(const Opcode& value) {
			// TODO
		}

		void CPU::_fx33(const Opcode& value) {
			// TODO
		}

		void CPU::_fx55(const Opcode& value) {
			auto register_index{(value >> 8) & 0xF};

			// Save the previous offset
			stack_->push(offset_);
			offset_ = registers_.index;

			// Fill the memory from Vx's
			for (auto vx{0}; vx <= register_index; ++vx)
				ram_->at(offset_++) = registers_.general->at(vx);

			// Restore the previous offset
			offset_ = stack_->top();
				stack_->pop();
		}

		void CPU::_fx65(const Opcode& value) {
			auto register_index{(value >> 8) & 0xF};

			// Save the previous offset
			stack_->push(offset_);
			offset_ = registers_.index;

			// Fill the Vx's from the memory
			for (auto vx{0}; vx <= register_index; ++vx)
				registers_.general->at(vx) = ram_->at(offset_++);

			// Restore the previous offset
			offset_ = stack_->top();
			stack_->pop();
		}
	} // namespace hw
} // namespace application