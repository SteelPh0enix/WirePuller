#ifndef GLOBALS_HPP
#define GLOBALS_HPP

using u8 = unsigned char;
using uint = unsigned;

// Application global variables
namespace Globals {
constexpr uint MaxJsonSize = 512u;
constexpr unsigned long SerialDataRate = 250000;
constexpr char JsonTerminator = '\n';
constexpr uint SerialTimeout = 500u;
}  // namespace Globals

#endif
