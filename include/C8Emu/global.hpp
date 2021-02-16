#pragma once

namespace constants {
    namespace stack {
        const int SIZE = 16;        // Size of a stack for CHIP-8 implementation
    }

    namespace memory {
        const int SIZE = 4096;      // Size of memory allocated for the emulation
        const int OFFSET = 512;     // Default offset in the memory
    }

    namespace cpu {
        const int REG = 16;         // Amount of internal registers of CHIP-8
    }
}