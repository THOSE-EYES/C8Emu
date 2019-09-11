#pragma once

#include <exception>
#include <string>

#define OPCODEERR 1
#define STFULLERROR 2
#define STEMPTYERROR 3
#define MEMRANGEOUTERR 4
#define FOPENERR 5
#define SLIBCHERR 6

/*ERROR CODES
	
	* 1 - (CPU) An opcode isn't recognized
	* 2 - (Memory) Stack is full and it's requested to put something in
	* 3 - (Memory) Stack is empty and it's requested to get an adress
	* 4 - (Memory) The requested block number is out of range of the memory 
	* 5 - (I/O) A file isn't opened
	* 6 - (Sound) API number is not correct
	...
*/

class Exception final : public std::exception {
protected :
	std::string error_message = "An error has occured. The code of the error is : ";
	unsigned char error_code;

public :
   explicit Exception(unsigned char);

   const char* what() const throw();

   const char code() const;	//It returns the code of an error
};

