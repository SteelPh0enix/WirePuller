#ifndef GLOBALS_HPP
#define GLOBALS_HPP

// Application global variables
namespace Globals {
constexpr unsigned MaxJsonSize = 512u;
constexpr unsigned long SerialDataRate = 250000;
constexpr char JsonTerminator = '\n';
constexpr unsigned SerialTimeout = 500u;
}  // namespace Globals

#endif
