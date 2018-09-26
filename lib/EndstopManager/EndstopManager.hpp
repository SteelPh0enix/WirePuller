#ifndef ENDSTOPMANAGER_HPP
#define ENDSTOPMANAGER_HPP
#include <string.h>
#include <Endstop.hpp>
#include <Globals.hpp>

//! Class for managing multiple endstops by their ID's
template <uint EndstopCountValue, uint MaxIDLengthValue>
class EndstopManager {
 public:
  //! Number of endstops managed by object
  static constexpr uint endstopCount = EndstopCountValue;

  //! Maximal ID length of endstop
  static constexpr uint maxIDLength = MaxIDLengthValue + 1;

  //! Initializes next endstop
  /*!
      \param id ID of the endstop
      \param endstopPin endstop pin

      \return true if initialized, false if all endstops are initialized
  */
  bool initializeEndstop(const char* id, u8 endstopPin) {
    if (m_initializedEndstops >= endstopCount) return false;

    strcpy(m_endstops[m_initializedEndstops].id, id);
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
  Endstop* operator[](const char* id) {
    for (uint i = 0; i < m_initializedEndstops; i++) {
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
  Endstop const* operator[](const char* id) const {
    for (uint i = 0; i < m_initializedEndstops; i++) {
      if (strcmp(m_endstops[i].id, id) == 0) {
        return &(m_endstops[i].endstop);
      }
    }

    return nullptr;
  }

  //! get count of initialized endstops
  /*!
      \return number of initialized endstops
  */
  uint initializedEndstops() const { return m_initializedEndstops; }

 protected:
  struct EndstopIDPair {
    Endstop endstop;
    char id[maxIDLength];
  };

  EndstopIDPair m_endstops[endstopCount];
  uint m_initializedEndstops{0};
};

#endif
