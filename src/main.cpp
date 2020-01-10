#include <map>
#include <iostream>

#ifdef DEBUG
	#include <gtest/gtest.h>
#endif

#include "cpu.h"
#include "memory.h"
#include "io.h"

#define MIN_ARGS 1

using namespace std;

map<string, string> parse(int argc, char *argv[]) {
	//Initialize local variables
	map<string, string> arguments = map<string, string>();
	string argument;

	//For each argument
	for (char** p_argument = &(argv[1]); p_argument != &(argv[argc]); ++p_argument) {
		//Make argument a string
		argument = string(*p_argument);

		//Make a map out of the argument
		arguments.insert(make_pair(argument.substr(0, argument.find("=")), \
			argument.substr(argument.find("=") + 1, argument.size())));
	}

	return arguments;
}

CPU* init(map<string, string> arguments) {
	CPU* cpu;
	Memory* memory = new Memory();
	string key, value;

	for (auto args_iter = arguments.begin(); args_iter != arguments.end(); ++args_iter) {
		key = args_iter->first;
		value = args_iter->second;

		if (key == "file") load(value, memory);
	}

	cpu = new CPU(memory);

	return cpu;
}

int main(int argc, char *argv[]) {
	#ifdef DEBUG
		::testing::InitGoogleTest(&argc, argv);
		RUN_ALL_TESTS();
	#endif

	//Check if there're enough arguments
	//if ((argc - 1) < MIN_ARGS) throw Exception(ARGSERROR);

	//Parse the arguments
	//map<string, string> arguments = parse(argc, argv);

	//Declare and initialize instances
	//CPU* cpu = init(arguments);

	//Start the emulation
	//cpu->emulateCycle();

	return 0;
}