#include "MC33926.hpp"
#include <Arduino.h>

MC33926::MC33926(uint8_t PWMPin, uint8_t directionPin, uint8_t feedbackPin, uint8_t disablePin,
                 uint8_t statusFlagPin) {
  setPins(PWMPin, directionPin, feedbackPin, disablePin, statusFlagPin);
}

void MC33926::setPins(uint8_t PWM, uint8_t direction, uint8_t feedback, uint8_t disable,
                      uint8_t statusFlag) {
  pinPWM = PWM;
  pinDirection = direction;
  pinFeedback = feedback;
  pinDisable = disable;
  pinStatusFlag = statusFlag;

  pinsHasBeenSet();
}

int MC33926::maxPower() const { return 255; }

bool MC33926::setPower(int power) {
  if (!initialized()) {
    return false;
  }

  bool reverse{false};

  power = constrain(power, -maxPower(), maxPower());
  actualPower = power;

  if (power < 0) {
    power *= -1;
    reverse = true;
  }

  analogWrite(pinPWM, power);
  digitalWrite(pinDirection, reverse);

  return true;
}

int MC33926::power() const { return actualPower; }

double MC33926::current() const {
  if (!initialized()) {
    return -1.;
  }

  return analogRead(pinFeedback) * CurrentMultiplier();
}

bool MC33926::error() const {
  if (!initialized()) {
    return true;
  }

  return !static_cast<bool>(digitalRead(pinStatusFlag));
}

bool MC33926::internalInitialize() {
  pinMode(pinPWM, OUTPUT);
  pinMode(pinDirection, OUTPUT);
  pinMode(pinFeedback, INPUT);
  pinMode(pinDisable, OUTPUT);
  pinMode(pinStatusFlag, INPUT);

  digitalWrite(pinDisable, HIGH);

  return true;
}
