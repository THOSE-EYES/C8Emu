 #include "application.hpp"

Application::Application(const int argc, char** argv) {
    // Parse the arguments
     _tokenizer.parse(argc, argv);

    // Initialize the application
    init();
}

Application::~Application() {
    delete _cpu;
}

void Application::init() {
	RAM* memory = new RAM(constants::memory::SIZE);                         // A new instance of memory to fill
    Stack* stack = new Stack(constants::stack::SIZE);                       // Stack instance
	std::string filename = _tokenizer.getValue("filename");                 // Temporary variable to store a filename of interest
    
    // Load the file into memory to execute
    memory->load(filename, constants::memory::OFFSET);

    // Create a new instance of CPU
	_cpu = new CPU(memory, stack);
}

void Application::start(void){
    // Start the main cycle
    _cpu->start();
}