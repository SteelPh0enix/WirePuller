#ifndef ENDSTOPMANAGER_HPP
#define ENDSTOPMANAGER_HPP
#include <Globals.hpp>
#include <Span.hpp>
#include <Endstop.hpp>
#include <string.h>

//! Class for managing multiple endstops by their ID's
template <uint EndstopCountValue, uint MaxIDLengthValue>
class EndstopManager {
public:
    //! Number of endstops managed by object
    static constexpr uint EndstopCount = EndstopCountValue;

    //! Maximal ID length of endstop
    static constexpr uint MaxIDLength = MaxIDLengthValue + 1;

    //! Alias for ID data type
    using ID = Span<char, MaxIDLength>;

    //! Initializes next endstop
    /*!
        \param id ID of the endstop
        \param endstopPin endstop pin

        \return true if initialized, false if all endstops are initialized
    */
    bool initializeEndstop(ID const& id,
                         u8 endstopPin) {
        if (m_initializedEndstops >= EndstopCount) return false;

        m_endstops[m_initializedEndstops].id = id;
        m_endstops[m_initializedEndstops].endstop.initialize(endstopPin);

        m_initializedEndstops++;
        return true;
    } 

    //! map-like access to endstop by it's ID
    /*!
        note: this will perform linear search, this is not a map!

        \param id endstop id
        \return a pointer to endstop, or nullptr if no endstop was found
    */
    Endstop* operator[](ID const& id) {
        for(uint i = 0; i < m_initializedEndstops; i++) {
            if (strcmp(m_endstops[i].id, id) == 0) {
                return &(m_endstops[i].endstop);
            }
        }

        return nullptr;
    } 

    //! map-like constant access to endstop by it's ID
    /*!
        note: this will perform linear search, this is not a map!

        \param id endstop id
        \return a pointer to endstop, or nullptr if no endstop was found
    */
    Endstop const* operator[](ID const& id) const {
        for(uint i = 0; i < m_initializedEndstops; i++) {
            if (strcmp(m_endstops[i].id, id) == 0) {
                return &(m_endstops[i].endstop);
            }
        }

        return nullptr;
    } 

protected:
    struct EndstopIDPair {
        Endstop endstop;
        ID id;
    };

    EndstopIDPair m_endstops[EndstopCount];
    uint m_initializedEndstops{ 0 };
};

#endif