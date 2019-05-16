#ifndef ENCODERMANAGER_HPP
#define ENCODERMANAGER_HPP
#include <Encoder.h>
#include <string.h>
#include <Globals.hpp>

template <unsigned EncoderCountValue, unsigned MaxIDLengthValue>
class EncoderManager {
 public:
  static constexpr unsigned encoderCount = EncoderCountValue;

  static constexpr unsigned maxIDLength = MaxIDLengthValue + 1;

 protected:
  struct EncoderIDPair {
    Encoder encoder;
    char id[maxIDLength];
  };

 public:
  bool initializeEncoder(char const* id) {
    if (m_intializedEncoders >= encoderCount) return false;

    strcpy(m_encoders[m_intializedEncoders].id, id);

    m_intializedEncoders++;
    return true;
  }

  Encoder* operator[](char const* id) {
    for (unsigned i = 0; i < m_intializedEncoders; i++) {
      if (strcmp(m_encoders[i].id, id) == 0) {
        return &(m_encoders[i].encoder);
      }
    }

    return nullptr;
  }

  Encoder const* operator[](char const* id) const {
    for (unsigned i = 0; i < m_intializedEncoders; i++) {
      if (strcmp(m_encoders[i].id, id) == 0) {
        return &(m_encoders[i].encoder);
      }
    }

    return nullptr;
  }

  unsigned initializedEncoders() const { return m_intializedEncoders; }

  EncoderIDPair* begin() { return m_encoders; }
  EncoderIDPair* end() { return &m_encoders[encoderCount]; }

 protected:
  // This is hardcoded because of now Encoder class is made.
  EncoderIDPair m_encoders[encoderCount]{{Encoder(18, 19), ""},
                                         {Encoder(20, 21), ""}};
  unsigned m_intializedEncoders{0};
};

#endif
