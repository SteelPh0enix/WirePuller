#pragma once
#include <stdint.h>
#include "../Module/Module.hpp"

class Endstop : public Module {
 public:
  Endstop() = default;
  Endstop(uint8_t pin);

  void setPins(uint8_t pin);

  void setPullup(bool pullupEnabled);
  bool pullupEnabled() const;

  // Sometimes, when setting input as pullup, readed values are inverted. Use it
  // to compenaste inversion and ensure that object will return `true` when
  // pressed, without having to manually negate the value
  void setOutputInversion(bool shouldNegate);
  bool outputInverted() const;

  bool read() const;

 private:
  uint8_t endstopPin{};
  bool isPullupEnabled{false};
  bool isOutputInverted{false};

  virtual bool internalInitialize() override;
};