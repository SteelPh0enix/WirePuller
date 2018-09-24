#ifndef UTILS_HPP
#define UTILS_HPP
#include <Globals.hpp>
#include <string.h>

//! Static data span for quality of life
template <typename T, uint SizeValue>
struct Span {
    //! Size of span data
    static constexpr uint Size = SizeValue;

    //! Alias for span type
    using Type = T;

    //! Raw data array
    Type ptr[Size];

    //! Sets whole span memory to 0
    void clear() {
        memset(ptr, 0, Size * sizeof(Type));
    }

    //! == operator overload
    /*!
        Note - it's not optimized for char arrays, as i should create a
        distinct class for it. Maybe later, in this project it's not necessary
        as i won't really keep long string in there.

        Workaround: use strcmp explicitly.
    */
    bool operator==(Span<Type, Size> const& other) {
        // I'm not comparing sizes because it should be done by compiler
        // (you can only pass a span for comparison with same type and size as original one)
        for(uint i = 0; i < Size; i++) {
            if (ptr[i] != other.ptr[i]) return false;
        }

        return true;
    }

    //! array-like access to data
    Type& operator[](uint i) { return ptr[i]; }

    //! array-like constant access to data
    Type const& operator[](uint i) const { return ptr[i]; }
};

#endif