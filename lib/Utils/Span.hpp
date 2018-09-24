#ifndef SPAN_HPP
#define SPAN_HPP
#include <Globals.hpp>
#include <string.h>

//! Static data span for quality of life
template <typename T, uint SizeValue>
struct Span {
    //! Alias for span type
    using Type = T;

    //! Length of span data
    static constexpr uint Length = SizeValue;

    //! Size of span data (in bytes)
    static constexpr uint Size = Length * sizeof(Type);

    //! Raw data array
    Type ptr[Length];

    //! Default constructor
    Span() = default;

    //! Initializing constructor
    Span(Type const data[Length]) {
        memcpy(ptr, data, Size);
    }

    //! Sets whole span memory to 0
    void clear() {
        memset(ptr, 0, Size);
    }

    //! == operator overload
    /*!
        Note - it's not optimized for char arrays, as i should create a
        distinct class for it. Maybe later, in this project it's not necessary
        as i won't really keep long string in there.

        Workaround: use strcmp explicitly.
    */
    bool operator==(Span<Type, Length> const& other) {
        // I'm not comparing sizes because it should be done by compiler
        // (you can only pass a span for comparison with same type and size as original one)
        for(uint i = 0; i < Length; i++) {
            if (ptr[i] != other.ptr[i]) return false;
        }

        return true;
    }

    //! Copy-constructor
    Span(Span<T, SizeValue> const& other) {
        memcpy(ptr, other.ptr, Size);
    }

    //! Move-constructor
    Span(Span<T, SizeValue>&& other) {
        ptr = other.ptr;
    }

    //! Copy assigment operator
    Span<T, SizeValue>& operator=(Span<T, SizeValue> const& other) {
        memcpy(ptr, other.ptr, Size);
        return *this;
    }

    //! Move assigment operator
    Span<T, SizeValue>& operator=(Span<T, SizeValue>&& other) {
        ptr = other.ptr;
        return *this;
    }

    //! array-like access to data
    Type& operator[](uint i) { return ptr[i]; }

    //! array-like constant access to data
    Type const& operator[](uint i) const { return ptr[i]; }
};

#endif