#pragma once

// Include C/C++ STL headers
#include <string>
#include <fstream>
#include <memory>

// Include project headers
#include "constants.hpp"
#include "exceptions.hpp"
#include "hw/cpu.hpp"
#include "ui/window.hpp"

namespace application {
    /**
     * This is the main application class that handles
     * CPU initializtion, file loading and GUI creation
     */
    class Application {
    public:
        /**
         * Constructor
         */
        Application(std::string filename);

    public:
        /**
         * Starting the emulation
         */
        void start();

        /**
         * Set the name of the file to execute a program from
         * @param value the name of the file
         */
        void set_file(const std::string& value);

        /**
         * Set the name of the file to execute a program from
         * @return the name of the file
         */
        const std::string& get_file() const noexcept;

    protected:
        /**
         * Load the file into the memory
         */
        virtual void load();

    private:
        std::unique_ptr<application::hw::CPU>       cpu_;		// A CPU instance to use as a core of the emulator
        std::shared_ptr<application::ui::Window>    window_;    // Window instance
        std::string                                 filename_;  // The name of the file to get a program from
    };
} // namespace application