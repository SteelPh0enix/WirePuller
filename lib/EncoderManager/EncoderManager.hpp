#ifndef ENCODERMANAGER_HPP
#define ENCODERMANAGER_HPP
#include <Encoder.h>
#include <string.h>
#include <Globals.hpp>

template <uint EncoderCountValue, uint MaxIDLengthValue>
class EncoderManager {
 public:
  static constexpr uint encoderCount = EncoderCountValue;

  static constexpr uint maxIDLength = MaxIDLengthValue + 1;

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
    for (uint i = 0; i < m_intializedEncoders; i++) {
      if (strcmp(m_encoders[i].id, id) == 0) {
        return &(m_encoders[i].encoder);
      }
    }

    return nullptr;
  }

  Encoder const* operator[](char const* id) const {
    for (uint i = 0; i < m_intializedEncoders; i++) {
      if (strcmp(m_encoders[i].id, id) == 0) {
        return &(m_encoders[i].encoder);
      }
    }

    return nullptr;
  }

  uint initializedEncoders() const { return m_intializedEncoders; }

  EncoderIDPair* begin() { return m_encoders; }
  EncoderIDPair* end() { return &m_encoders[encoderCount]; }

 protected:
  // This is hardcoded because of now Encoder class is made.
  EncoderIDPair m_encoders[encoderCount]{{Encoder(18, 19), ""},
                                         {Encoder(20, 21), ""}};
  uint m_intializedEncoders{0};
};

#endif
