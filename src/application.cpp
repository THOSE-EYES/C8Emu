 #include "application.hpp"

Application::Application(std::string filename) {
	setFile(filename);

    // Initialize the application
    init();
}

Application::~Application() {}

void Application::init() {
	RAM* memory = new RAM(constants::memory::SIZE);                         // A new instance of memory to fill
    Stack* stack = new Stack(constants::stack::SIZE);                       // Stack instance
    
    // Load the file into memory to execute
    memory->load(_filename, constants::memory::OFFSET);

    // Create a new instance of CPU
	_cpu = std::unique_ptr<CPU>(new CPU(memory, stack));
}

void Application::start(void){
    // Start the main cycle
    _cpu->start();
}

void Application::setFile(std::string filename) {
	if (filename.size() == 0)
		throw new std::invalid_argument("Filename can't be empty"); 

	_filename = filename;
}