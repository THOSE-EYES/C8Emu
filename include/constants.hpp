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