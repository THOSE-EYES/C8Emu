#pragma once

// Include C/C++ STL headers
#include <exception>
#include <string>

namespace application {
	namespace exceptions {
		namespace hw {
			namespace cpu {
				/**
				 * The exception is thrown when there is
				 * an unexpected opcode
				 */
				class InvalidOpcodeException final : public std::exception {
				private:
					uint16_t opcode_;
					std::string message_{"Unexpected opcode : "};

				public:
					/**
					 * Constructor
					 * @param opcode the opcode that caused the exception
					 */
					InvalidOpcodeException(const uint16_t& opcode) : 
						opcode_{opcode} {
						message_ += std::to_string(opcode_);
					}
				
				public:
					/**
					 * Get the message about the error
					 * @return C-style message
					 */
					const char* what() const throw() {
						return message_.c_str();
					}
				};

				/**
				 * The exception is thrown when there is no
				 * return adress from the subroutine
				 */
				class InvalidSubroutineException final : public std::exception {
				private:
					std::string message_{"Invalid subroutine"};

				public:
					/**
					 * Constructor
					 */
					InvalidSubroutineException() = default;

				public:
					/**
					 * Get the message about the error
					 * @return C-style message
					 */
					const char* what() const throw() {
						return message_.c_str();
					}
				};
			} // namespace cpu
		} // namespace hw

		namespace ui {
			/**
			 * The exception is thrown when there is
			 * an unexpected opcode
			 */
			class InvalidTitleException final : public std::exception {
			private:
				std::string title_;
				std::string message_{"Window title is incorrect : "};

			public:
				/**
				 * Constructor
				 * @param title the opcode that caused the exception
				 */
				InvalidTitleException(const std::string& title) : 
					title_{title} {
					message_ += title;
				}
				
			public:
				/**
				 * Get the message about the error
				 * @return C-style message
				 */
				const char* what() const throw() {
					return message_.c_str();
				}
			};
		} // namespace ui

		/**
		 * The exception is thrown when there is
		 * an unexpected opcode
		 */
		class InvalidFileException final : public std::exception {
		private:
			std::string file_;
			std::string message_{"Unexpected opcode : "};

		public:
			/**
			 * Constructor
			 * @param opcode the opcode that caused the exception
			 */
			InvalidFileException(const std::string& file) : 
				file_{file} {
				message_ += file;
			}
				
		public:
			/**
			 * Get the message about the error
			 * @return C-style message
			 */
			const char* what() const throw() {
				return message_.c_str();
			}
		};
	} // namespace exceptions
} // namespace application