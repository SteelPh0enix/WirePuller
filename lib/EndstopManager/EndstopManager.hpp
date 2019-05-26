#ifndef ENDSTOPMANAGER_HPP
#define ENDSTOPMANAGER_HPP
#include <string.h>
#include <Endstop.hpp>
#include <Globals.hpp>

//! Class for managing multiple endstops by their ID's
template <unsigned EndstopCountValue, unsigned MaxIDLengthValue>
class EndstopManager {
 public:
  //! Number of endstops managed by object
  static constexpr unsigned endstopCount = EndstopCountValue;

  //! Maximal ID length of endstop
  static constexpr unsigned maxIDLength = MaxIDLengthValue + 1;

 protected:
  struct EndstopIDPair {
    Endstop endstop;
    char id[maxIDLength];
  };

 public:
  //! Initializes next endstop
  /*!
      \param id ID of the endstop
      \param endstopPin endstop pin

      \return true if initialized, false if all endstops are initialized
  */
  bool initializeEndstop(char const* id, uint8_t endstopPin) {
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
  Endstop* operator[](char const* id) {
    for (unsigned i = 0; i < m_initializedEndstops; i++) {
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
  Endstop const* operator[](char const* id) const {
    for (unsigned i = 0; i < m_initializedEndstops; i++) {
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
  unsigned initializedEndstops() const { return m_initializedEndstops; }

  EndstopIDPair const* begin() const { return m_endstops; }
  EndstopIDPair const* end() const { return &m_endstops[endstopCount]; }

 protected:
  EndstopIDPair m_endstops[endstopCount];
  unsigned m_initializedEndstops{0};
};

#endif