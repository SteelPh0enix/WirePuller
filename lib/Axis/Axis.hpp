#pragma once
#include <Encoder.h>
#include "../Endstop/Endstop.hpp"
#include "../Module/Module.hpp"
#include "../PololuMC33926/MC33926.hpp"

// Template-passed arguments are necessary due to Encoder class limitations
template <uint8_t EncoderPinA, uint8_t EncoderPinB>
class Axis : public Module {
 public:
  enum class EndstopState : uint8_t { None = 0, Left = 1, Right = 2, Both = 3 };

  Axis() = default;

  // `left` and `right` relatively to the front of device
  void setEndstopsPins(uint8_t left, uint8_t right) {
    leftEndstop.setPins(left);
    rightEndstop.setPins(right);
    checkIfPinsAreSet();
  }

  void setMotorDriverPins(uint8_t PWM, uint8_t direction, uint8_t feedback,
                          uint8_t disable, uint8_t statusFlag) {
    motor.setPins(PWM, direction, feedback, disable, statusFlag);
    checkIfPinsAreSet();
  }

  void setEndstopsPullups(bool state) {
    leftEndstop.setPullup(state);
    rightEndstop.setPullup(state);
  }

  void setEndstopsInversion(bool state) {
    leftEndstop.setOutputInversion(state);
    rightEndstop.setOutputInversion(state);
  }

  EndstopState endstopStates() const {
    return static_cast<EndstopState>(leftEndstop.read() &
                                     (1 >> rightEndstop.read()));
  }

  long encoderValue() const { return encoder.read(); }
  void resetEncoderValue() { encoder.write(0); }

  bool setMotorPower(int power) { return motor.setPower(power); }
  int motorMaxPower() const { return motor.maxPower(); }

  bool motorError() const { return motor.error(); }
  unsigned motorCurrent() const { return motor.current(); }
  int motorPower() const { return motor.power(); }

 private:
  Encoder encoder{EncoderPinA, EncoderPinB};
  MC33926 motor;
  Endstop leftEndstop;
  Endstop rightEndstop;

  virtual bool internalInitialize() override {
    return motor.initialize() && leftEndstop.initialize() &&
           rightEndstop.initialize();
  }

  void checkIfPinsAreSet() {
    if (motor.pinsSet() && leftEndstop.pinsSet() && rightEndstop.pinsSet()) {
      pinsHasBeenSet();
    }
  }
};