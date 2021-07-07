/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

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