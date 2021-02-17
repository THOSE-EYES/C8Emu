#pragma once

#include "ram.hpp"
#include "stack.hpp"
#include "global.hpp"
#include "cpu.hpp"

#include <string>
#include <fstream>
#include <memory>

class Application final {
private:
    //CPU* _cpu;					// A CPU instance to use as a core of the emulator
    std::unique_ptr<CPU> _cpu;		// A CPU instance to use as a core of the emulator
    std::string _filename;

    /**
     * Initialization of the main instances to run the emulation
     * @param arguments - std::map of the parsed arguments
     */
    void init();

	/**
	 * 
	 */
	void setFile(std::string filename);

public:
    /**
     * Constructor
     */
    Application(std::string filename);

    /**
     * Destructor
     */
    ~Application();

    /**
     * Starting the emulation
     */
    void start(void);



};