#pragma once
#include <stdint.h>
#include "../Module/Module.hpp"

class MC33926 : public Module {
 public:
  MC33926() = default;
  MC33926(uint8_t PWMPin, uint8_t directionPin, uint8_t feedbackPin,
          uint8_t disablePin, uint8_t statusFlagPin);

  void setPins(uint8_t PWM, uint8_t direction, uint8_t feedback,
               uint8_t disable, uint8_t statusFlag);

  int maxPower() const;
  bool setPower(int power);
  int power() const;

  double current() const;
  bool error() const;

 private:
  virtual bool internalInitialize() override;

  uint8_t pinPWM{};
  uint8_t pinDirection{};
  uint8_t pinFeedback{};
  uint8_t pinDisable{};
  uint8_t pinStatusFlag{};

  int actualPower{};

  constexpr static double FeedbackVoltsPerAmp{0.525};
  constexpr static double CurrentMultiplier() {
    return Module::DefaultADCVoltage<double>() /
           Module::ADCResolution<double>() / FeedbackVoltsPerAmp;
  }
};