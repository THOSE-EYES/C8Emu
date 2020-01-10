#pragma once

#include <exception>
#include <string>
#include <iostream>
#include <cstdlib>

#define ARGSERROR 1
#define OPCODEERR 2
#define STFULLERROR 3
#define STEMPTYERROR 4
#define MEMRANGEOUTERR 5
#define FOPENERR 6
#define SLIBCHERR 7

/*ERROR CODES
	* 1 - (Main) Not enough arguments
	* 2 - (CPU) An opcode isn't recognized
	* 3 - (Memory) Stack is full and it's requested to put something in
	* 4 - (Memory) Stack is empty and it's requested to get an adress
	* 5 - (Memory) The requested block number is out of range of the memory 
	* 6 - (I/O) A file isn't opened
	* 7 - (Sound) API number is not correct
	...
*/

class Exception final : public std::exception {
protected :
	std::string error;

public :
   explicit Exception(unsigned int);

   const char* what() const throw();
};

