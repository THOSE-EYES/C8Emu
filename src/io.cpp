#include "io.h"

void load(const std::string file, Memory* memory) {
	//Open the program
	std::fstream stream(file, std::ios::in | std::ios::binary);

	if (!stream.is_open()) throw Exception(FOPENERR);

	//Move the pointer to the right place in the memory
	memory->move(OFFSET);

	//Write the program into the memory while it's not the end of the file
	while (!stream.eof()) { 
		memory->write_byte(stream.get());
	}
}