#ifndef GLOBALS_HPP
#define GLOBALS_HPP

using u8 = unsigned char;
using uint = unsigned;

// Application global variables
namespace Globals {
    constexpr uint MaxJsonSize = 256u;
    constexpr unsigned long SerialDataRate = 115200u;
    constexpr char JsonTerminator = '\n';
}

#endif