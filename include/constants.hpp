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
#include <cstdint>

namespace constants {
    namespace stack {
        const int size{16};        // Size of a stack for CHIP-8 implementation
    } //namespace stack

    namespace ram {
        const uint32_t size{4096};      // Size of memory allocated for the emulation
        const uint32_t offset{512};     // Default offset in the memory
    } // namespace ram

    namespace cpu {
        const int32_t registers{16};         // Amount of internal registers of CHIP-8
    } // namespace cpu

	namespace window {
		const uint8_t   max_title_size{255};
		const uint16_t  min_height{480};
		const uint16_t  min_width{800};
	} // namespace window

    namespace utils {
        const std::string settings_file{"settings.dat"};
    }
}