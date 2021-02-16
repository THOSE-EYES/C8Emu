#include "exceptions.hpp"

Exception::Exception(unsigned int code) {
	error = " An error has occured. The code of the error is : ";
	error += std::to_string(code);
}

const char* Exception::what() const throw() {
	return error.c_str();
}