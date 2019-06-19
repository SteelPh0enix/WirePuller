#pragma once
#include <Encoder.h>
#include "../Endstop/Endstop.hpp"
#include "../Module/Module.hpp"
#include "../PololuMC33926/MC33926.hpp"

// Template-passed arguments are necessary due to Encoder class limitations. DO
// NOT PASS AS CONST if you want to be able to read encoder value.
template <uint8_t EncoderPinA, uint8_t EncoderPinB>
class Axis : public Module {
 public:
  enum class EndstopsState : uint8_t { None = 0, Left = 1, Right = 2, Both = 3 };

  Axis() = default;

  // `left` and `right` relatively to the front of device
  void setEndstopsPins(uint8_t left, uint8_t right) {
    if (endstopsEnabled()) {
      leftEndstop.setPins(left);
      rightEndstop.setPins(right);
    }
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

  EndstopsState endstopsState() const {
    if (endstopsEnabled()) {
      uint8_t endstopsFlag = leftEndstop.read();
      if (rightEndstop.read()) endstopsFlag |= 2;

      return static_cast<EndstopsState>(endstopsFlag);
    } else {
      return EndstopsState::None;
    }
  }

  long encoderValue() { return encoder.read(); }
  void resetEncoderValue() { encoder.write(0); }

  bool setMotorPower(int power) { return motor.setPower(power); }
  int motorMaxPower() const { return motor.maxPower(); }

  bool motorError() const { return motor.error(); }
  double motorCurrent() const { return motor.current(); }
  int motorPower() const { return motor.power(); }

  void enableEndstops() { endstopsAreEnabled = true; }
  void disableEndstops() { endstopsAreEnabled = false; }
  bool endstopsEnabled() const { return endstopsAreEnabled; }

  void checkPinsInitialization() { checkIfPinsAreSet(); }

  bool stopOnEndstopHit() {
    if (!endstopsEnabled() || !initialized()) {
      return false;
    }

    if (endstopsState() != EndstopsState::None) {
      setMotorPower(0);
      return true;
    }

    return false;
  }

  void callibrate(EndstopsState whichEndstop, bool waitForCallibration = true) {
    if (!endstopsEnabled()) {
      return;
    }

    switch (whichEndstop) {
      case EndstopsState::Left: {
        setMotorPower(-motorMaxPower());
        break;
      }
      case EndstopsState::Right: {
        setMotorPower(motorMaxPower());
        break;
      }
      default: { return; }
    }

    if (waitForCallibration) {
      while (!stopOnEndstopHit())
        ;
      resetEncoderValue();
    }
  }

 private:
  Encoder encoder{EncoderPinA, EncoderPinB};
  MC33926 motor;
  Endstop leftEndstop;
  Endstop rightEndstop;

  bool endstopsAreEnabled{true};

  virtual bool internalInitialize() override {
    return motor.initialize() && (!endstopsEnabled() || (leftEndstop.initialize() && rightEndstop.initialize()));
  }

  void checkIfPinsAreSet() {
    if (motor.pinsSet() &&
        (!endstopsEnabled() || (leftEndstop.pinsSet() && rightEndstop.pinsSet()))) {
      pinsHasBeenSet();
    }
  }
};