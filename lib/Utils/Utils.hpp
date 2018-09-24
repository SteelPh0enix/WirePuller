#ifndef UTILS_HPP
#define UTILS_HPP
#include <Globals.hpp>

//! Static bytes span for easier data manipulation
template <uint BytesSize>
struct Bytes {
    static constexpr uint Size = BytesSize;
    byte ptr[BytesSize];

    byte& operator[](uint i) { return ptr[i]; }
    byte const& operator[](uint i) const { return ptr[i]; }
};

#endif