#pragma once

// Include C++/C STL headers
#include <experimental/random>
#include <deque>
#include <stack>
#include <memory>
#include <limits>

// Include project headers
#include "hw/gpu.hpp"
#include "hw/keyboard.hpp"
#include "hw/soundcard.hpp"
#include "constants.hpp"
#include "exceptions.hpp"

namespace application {
	namespace hw {
		/**
		 * Class represents the CPU chip, which was designed
		 * to execute a special set of commands
		 */
		class CPU {
		public: 
			using RAM 				= std::deque<uint8_t>;
			
		protected:
			using GeneralRegister 	= uint8_t;
			using GeneralRegisters	= std::deque<GeneralRegister>;
			using Stack 			= std::stack<uint16_t>;
			using Opcode 			= uint16_t;

		public:
			/**
			 * Constructor
			 */
			CPU();

		public:
			/**
			 * Statring to execute the main loop
			 */
			virtual void start();

			/**
			 * Reset the CPU
			 */
			virtual void reset();

			/**
			 * Get the pointer to the RAM instance
			 * @return the pointer
			 */
			virtual std::shared_ptr<CPU::RAM> ram() const noexcept;

			/**
			 * Get the pointer to the GPU
			 * @return the pointer
			 */
			virtual std::shared_ptr<application::hw::GPU> gpu() const noexcept;

		protected:
			/**
			 * Struct of CPU registers
			 */
			struct Registers {
				std::unique_ptr<GeneralRegisters> general;	// Vector of general registers
				uint16_t index{0};							// Index register
			};

			/**
			 * Struct of CPU timers
			 */
			struct Timers {
				uint8_t delay{0};	// Delay timer
				uint8_t sound{0};	// Sound timer
			};

			/**
			 * Struct of CPU flags
			 */
			struct Flags {
				bool running{false};	// Flag of execution

				// FIXME : remove
				bool carry{false};		// Carry flag
				bool overflow{false};	// Overflow flag
				bool borrow{false};		// Borrow flag
			};

		protected:			
			std::shared_ptr
				<application::hw::GPU>		gpu_;								// GPU instance
			std::unique_ptr
				<application::hw::Keyboard> keyboard_;							// Keyboard handler
			std::shared_ptr<RAM> 			ram_;								// Instance of virtual memory
			uint16_t 						offset_{constants::ram::offset};	// Memory offset used to execute programs from RAM
			std::unique_ptr<Stack> 			stack_;								// CPU stack
			Registers 						registers_;							// Instance of CPU register set
			Timers 							timers_;							// Internal CPU timers
			Flags 							flags_;								// Processor flags

		protected:
			/**
			 * Executing opcodes, specific for the CHIP-8 interpretator
			 * @param opcode - data to process
			 */
			virtual void execute(const Opcode& opcode);

			/**
			 * Checking if there was an interrupt event
			 */
			virtual void interrupt();

		protected:
			/**
			 * Exit the app
			 */
			virtual void _0000();

			/**
			 * Exit from the subroutine
			 */
			virtual void _00ee();

			/**
			 * Clear GPU buffer
			 */
			virtual void _00e0();

			/**
			 * Calls RCA 1802 program at address NNN. 
			 * Not necessary for most ROMs
			 */
			virtual void _0nnn();

			/**
			 * Jumps to address NNN
			 * @param value the opcode to extract data from
			 */
			virtual void _1nnn(const Opcode& value);

			/**
			 * Calls subroutine at NNN
			 * @param value the opcode to extract data from
			 */
			virtual void _2nnn(const Opcode& value);

			/**
			 * Skips the next instruction if VX equals NN
			 * @param value the opcode to extract data from
			 */
			virtual void _3xnn(const Opcode& value);

			/**
			 * Skips the next instruction if VX doesn't equal NN
			 * @param value the opcode to extract data from
			 */
			virtual void _4xnn(const Opcode& value);

			/**
			 * Skips the next instruction if VX equals VY
			 * @param value the opcode to extract data from
			 */
			virtual void _5xy0(const Opcode& value);

			/**
			 * Sets VX to NN
			 * @param value the opcode to extract data from
			 */
			virtual void _6xnn(const Opcode& value);

			/**
			 * Adds NN to VX (carry flag is not changed)
			 * @param value the opcode to extract data from
			 */
			virtual void _7xnn(const Opcode& value);

			/**
			 * Sets VX to the value of VY
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy0(const Opcode& value);

			/**
			 * Sets VX to VX or VY (bitwise OR operation)
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy1(const Opcode& value);

			/**
			 * Sets VX to VX and VY (bitwise AND operation)
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy2(const Opcode& value);

			/**
			 * Sets VX to VX xor VY
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy3(const Opcode& value);

			/**
			 * Adds VY to VX. VF is set to 1 when there's a 
			 * carry, and to 0 when there isn't
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy4(const Opcode& value);

			/**
			 * VY is subtracted from VX. VF is set to 0 
			 * when there's a borrow, and 1 when there isn't
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy5(const Opcode& value);

			/**
			 * Stores the least significant bit of VX in VF 
			 * and then shifts VX to the right by 1
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy6(const Opcode& value);

			/**
			 * Sets VX to VY minus VX. VF is set to 0 when 
			 * there's a borrow, and 1 when there isn't
			 * @param value the opcode to extract data from
			 */
			virtual void _8xy7(const Opcode& value);

			/**
			 * Stores the most significant bit of VX in VF 
			 * and then shifts VX to the left by 1
			 * @param value the opcode to extract data from
			 */
			virtual void _8xye(const Opcode& value);

			/**
			 * Skips the next instruction if VX doesn't equal VY
			 * @param value the opcode to extract data from
			 */
			virtual void _9xy0(const Opcode& value);

			/**
			 * Sets I to the address NNN
			 * @param value the opcode to extract data from
			 */
			virtual void _annn(const Opcode& value);

			/**
			 * Jumps to the address NNN plus V0
			 * @param value the opcode to extract data from
			 */
			virtual void _bnnn(const Opcode& value);

			/**
			 * Sets VX to the result of a bitwise and operation 
			 * on a random number (typically: 0 to 255) and NN
			 * @param value the opcode to extract data from
			 */
			virtual void _cxnn(const Opcode& value);

			/**
			 * Draws a sprite at coordinate (VX, VY) that has a 
			 * width of 8 pixels and a height of N pixels. Each 
			 * row of 8 pixels is read as bit-coded starting 
			 * from memory location I; I value doesn’t change 
			 * after the execution of this instruction. As 
			 * described above, VF is set to 1 if any screen 
			 * pixels are flipped from set to unset when the 
			 * sprite is drawn, and to 0 if that doesn’t happen
			 * @param value the opcode to extract data from
			 */
			virtual void _dxyn(const Opcode& value);

			/**
			 * Skips the next instruction if the key stored in VX is pressed
			 * @param value the opcode to extract data from
			 */
			virtual void _ex9e(const Opcode& value);

			/**
			 * Skips the next instruction if the key stored in VX isn't pressed
			 * @param value the opcode to extract data from
			 */
			virtual void _exa1(const Opcode& value);

			/**
			 * Sets VX to the value of the delay timer
			 * @param value the opcode to extract data from
			 */
			virtual void _fx07(const Opcode& value);

			/**
			 * A key press is awaited, and then stored in VX
			 * @param value the opcode to extract data from
			 */
			virtual void _fx0a(const Opcode& value);

			/**
			 * Sets the delay timer to VX
			 * @param value the opcode to extract data from
			 */
			virtual void _fx15(const Opcode& value);

			/**
			 * Sets the sound timer to VX
			 * @param value the opcode to extract data from
			 */
			virtual void _fx18(const Opcode& value);

			/**
			 * Adds VX to I
			 * @param value the opcode to extract data from
			 */
			virtual void _fx1e(const Opcode& value);

			/**
			 * Sets I to the location of the sprite for the character 
			 * in VX. Characters 0-F (in hexadecimal) are represented 
			 * by a 4x5 font
			 * @param value the opcode to extract data from
			 */
			virtual void _fx29(const Opcode& value);

			/**
			 * Stores the binary-coded decimal representation of VX, 
			 * with the most significant of three digits at the 
			 * address in I, the middle digit at I plus 1, and the 
			 * least significant digit at I plus 2
			 * @param value the opcode to extract data from
			 */
			virtual void _fx33(const Opcode& value);

			/**
			 * Stores V0 to VX (including VX) in memory starting 
			 * at address I.The offset from I is increased by 1 
			 * for each value written, but I itself is left unmodified
			 * @param value the opcode to extract data from
			 */
			virtual void _fx55(const Opcode& value);

			/**
			 * Fills V0 to VX (including VX) with values from 
			 * memory starting at address I. The offset from 
			 * I is increased by 1 for each value written, but 
			 * I itself is left unmodified
			 * @param value the opcode to extract data from
			 */
			virtual void _fx65(const Opcode& value);
		};
	} // namespace hw
} // namespace application