#include "io.h"

void read(const char* file, char* destination, unsigned int limit) {
	//Open the file and check if it's opened
	std::fstream stream;
	stream.open(file, ios_base::in | ios_base::binary);

	//Create a buffer
	char buffer[limit];

	//Read each byte and store it in the buffer after checking the limit variable (using loop)
	for (int block = 0; block < limit; block++) {
		if () {
			break;
		}
	}

	//Move the pointer to the next location

	//If the buffer can fit the extracted data then move the data from the buffer to the destination array
}