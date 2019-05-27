#pragma once
#include <Encoder.h>
#include "../Endstop/Endstop.hpp"
#include "../Module/Module.hpp"
#include "../PololuMC33926/MC33926.hpp"

template <uint8_t EncoderPinA, uint8_t EncoderPinB>
class Axis : public Module {
 public:
  enum class EndstopState : uint8_t { None = 0, Left = 1, Right = 2, Both = 3 };
  Axis() = default;

  // left and right relatively to the front of device
  void setEndstopsPins(uint8_t left, uint8_t right) {}
  void setMotorDriverPins(uint8_t PWM, uint8_t direction, uint8_t feedback,
                          uint8_t disable, uint8_t statusFlag) {}

 private:
  long encoderPosition{0};

  Encoder encoder{EncoderPinA, EncoderPinB};
  MC33926 motor;
  Endstop leftEndstop;
  Endstop rightEndstop;

  virtual bool internalInitialize() override {
    return motor.initialize() && leftEndstop.initialize() &&
           rightEndstop.initialize();
  }
};