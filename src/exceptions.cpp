#include "exceptions.h"

Exception::Exception(unsigned char code) {
	error_message = "An error has occured. The code of the error is : " + error_code;
	error_code = code;
}

const char* Exception::what() const throw() {
	return error_message.c_str();
}

const char Exception::code() const {
	return error_code;
}