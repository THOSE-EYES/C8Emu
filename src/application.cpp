#include "application.h"

Application::Application(const int argc, char** argv) {
    std::map<std::string, std::string> 
        arguments = parse(argc, argv);          // Parsed arguments

    // Initialize the application
    init(arguments);
}

Application::~Application() {
    delete _cpu;
}

void Application::init(std::map<std::string, std::string> arguments) {
	RAM* memory = new RAM(MEM_SIZE);                            // A new instance of memory to fill
    Stack* stack = new Stack(STACK_SIZE);                       // Stack instance
    std::map<std::string, std::string>::iterator iter;          // Temporary iterator used to find keys inside of an std::map
	std::string filename;                                       // Temporary variable to store a filename of interest

    // Move the pointer of RAM to the default offset 
    memory->move(OFFSET);
    
    // Find a filename in arguments
    iter = arguments.find("file");
    
    // Check if filename was specified
    if (iter == arguments.end()) throw Exception(ARGERR);
    
    // Fill the memory
    filename = iter->second;
    load(filename, memory);

    // TODO : Add other arguments 

    // Create a new instance of CPU
	_cpu = new CPU(memory, stack);
}

void Application::load(const std::string file, RAM* memory) {
    unsigned short memory_offset = memory->getAdress();                 // Current offset in the memory
	std::fstream stream(file, std::ios::in | std::ios::binary);         // Stream to read the specified file
    char byte;                                                          // Temporary variable for storing read bytes

    // Throw an exception if 
	if (!stream.is_open()) throw Exception(FOPENERR);

	//Write the program into the memory while it's not the end of the file
	while (!stream.eof()) {
        // Read exactly ONE byte from the file
        stream.read(&byte, 1);

        // Write a byte from the stream
		memory->write(byte);

        // Move the offset
        ++memory_offset;

        // Move the pointer to the right place in the memory
	    memory->move(memory_offset);
	}
}

std::map<std::string, std::string> Application::parse(const int argc, char** argv) {
	std::map<std::string, std::string> 
        arguments = std::map<std::string, std::string>();       // Storing parsed arguments
	std::string argument;                                       // Temporary variable for storing tokens

	// Iterate over an array of arguments
	for (char** p_argument = &(argv[1]); p_argument != &(argv[argc]); ++p_argument) {
		// Cast a char array to a string
		argument = std::string(*p_argument);

		//Make a map out of the argument
		arguments.insert(make_pair(argument.substr(0, argument.find("=")), \
			argument.substr(argument.find("=") + 1, argument.size())));
	}

	return arguments;
}

void Application::start(void){
    // Start the main cycle
    _cpu->start();
}