#pragma once

#include "ram.h"
#include "stack.h"
#include "global.h"
#include "exceptions.h"
#include "cpu.h"

#include <map>
#include <string>
#include <algorithm>
#include <fstream>

class Application final {
private:
    CPU* _cpu;                      // A CPU instance to use as a core of the emulator

    /**
     * Loading a game/program into the CHIP-8 memory
     * @param filename - name of the file to be loaded
     * @param memory - a pointer to preallocated instance of RAM for the emulator
     */
    void load(const std::string, RAM*);

    /**
     * Parsing arguments from main()
     * @param argc - amount of arguments that would've been passed
     * @param argv - arguments
     * @return - parsed arguments packed into std::map for convinience
     */
    std::map<std::string, std::string> parse(const int, char**);

public:
    /**
     * Constructor
     * @param argc - amount of arguments that would've been passed
     * @param argv - arguments
     */
    Application(const int, char**);

    /**
     * Destructor
     */
    ~Application();

    /**
     * Starting the emulation
     */
    void start(void);

    /**
     * Initialization of the main instances to run the emulation
     * @param arguments - std::map of the parsed arguments
     */
    void init(std::map<std::string, std::string>);
};