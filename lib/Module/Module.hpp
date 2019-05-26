#pragma once

/*
  Base class for every initializable module which needs physical pins, and
  initialization. Every class inheriting this interface should provide:
  * internalInitialize implementation, returning initialization result (true
    for success)
  * setPins function, which will call `pinsHasBeenSet` function after setting
  pins up.
*/

class Module {
 public:
  // Resolution constants. Change them in case of moving code to another
  // microcontroller
  template <typename T>
  static constexpr T ADCResolution() {
    return 1024.;
  }

  template <typename T>
  static constexpr T PWMResolution() {
    return 256.;
  }

  template <typename T>
  static constexpr T DefaultADCVoltage() {
    return 5.;
  }

  template <typename T>
  static constexpr T VoltsPerADCUnit(T ADCVoltage = DefaultADCVoltage()) {
    return ADCVoltage / ADCResolution<T>();
  }

  virtual ~Module() = default;

  bool initialize() {
    if (!pinsSet()) {
      return false;
    }

    return internalInitialize();
  }

  bool initialized() const { return isInitialized; }
  bool pinsSet() const { return arePinsSet; }

 protected:
  virtual bool internalInitialize() = 0;
  void pinsHasBeenSet() { arePinsSet = true; }

 private:
  bool arePinsSet{false};
  bool isInitialized{false};
};
