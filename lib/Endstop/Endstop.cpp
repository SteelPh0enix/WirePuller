#include "Endstop.hpp"
#include <Arduino.h>

Endstop::Endstop(uint8_t pin) { setPins(pin); }

void Endstop::setPins(uint8_t pin) {
  endstopPin = pin;
  pinsHasBeenSet();
}

bool Endstop::internalInitialize() {
  if (pullupEnabled()) {
    pinMode(endstopPin, INPUT_PULLUP);
  } else {
    pinMode(endstopPin, INPUT);
  }

  return true;
}

void Endstop::setPullup(bool pullupEnabled) { isPullupEnabled = pullupEnabled; }

bool Endstop::pullupEnabled() const { return isPullupEnabled; }

void Endstop::setOutputInversion(bool shouldNegate) {
  isOutputInverted = shouldNegate;
}

bool Endstop::outputInverted() const { return isOutputInverted; }

bool Endstop::read() const {
  if (!initialized()) {
    return false;
  }

  auto status = static_cast<bool>(digitalRead(endstopPin));

  if (outputInverted()) {
    return !status;
  } else {
    return status;
  }
}