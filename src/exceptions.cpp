#include "exceptions.h"

Exception::Exception(unsigned char code) {
	error_message = "An error has occured. The code of the error is : ";
	error_code = code;
}

const char* Exception::what() {
	return (error_message + error_code).c_str();
}

const char Exception::code() {
	return error_code;
}