#pragma once

#include "ram.hpp"
#include "stack.hpp"
#include "global.hpp"
#include "exceptions.hpp"
#include "cpu.hpp"
#include "tokenizer.hpp"

#include <map>
#include <string>
#include <algorithm>
#include <fstream>

class Application final {
private:
    CPU* _cpu;                                          // A CPU instance to use as a core of the emulator
    Tokenizer<std::string, std::string> _tokenizer;     // Tokenizer instance where all the arguments wiil be stored

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
    void init();
};