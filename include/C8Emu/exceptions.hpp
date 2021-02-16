#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <cstdlib>

#define ARGSERROR 1
#define FOPENERR 2
#define OPCODEERR 3
#define NULLPTRERR 4
#define STFULLERROR 5
#define STEMPTYERROR 6
#define STWRONGSZERR 7
#define MEMRANGEOUTERR 8
#define SMALLMEMSZERR 9
#define TNOTFOUND 10

/** ERROR CODES
 * 1 - (Application) Not enough arguments
 * 2 - (Application) A file isn't opened
 * 3 - (CPU) An opcode isn't recognized
 * 4 - (CPU) CPU's got null pointers to the memory
 * 5 - (Stack) Stack is full and it's requested to put something in
 * 6 - (Stack) Stack is empty and it's requested to get an adress
 * 7 - (Stack) Requested size is wrong (size < 1)
 * 8 - (RAM) The requested block number is out of range of the memory 
 * 9 - (RAM) The size of a requested virtual RAM is less than 1
 * 10 - (Tokenizer) Token was not found 
 */

class Exception final : public std::exception {
protected :
	std::string error;			// Description of the error

public :
	/**
	 * Constructor
	 * @param code - code of the error which's occurred
	 */
	explicit Exception(unsigned int);

	/**
	 * Printing the details of the error
	 */
	const char* what() const throw();
};

