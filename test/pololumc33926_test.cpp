#include <Arduino.h>
#include <PololuMC33926.hpp>

PololuMC33926 motor;
// PololuMC33926::Pinout pinout{6, 29, A2, 25, 24}; // M1
// PololuMC33926::Pinout pinout{7, 30, A0, 23, 22}; // M2
PololuMC33926::Pinout pinout{8, 31, A1, 23, 22};  // M3

void setup() { motor.initialize(pinout); }

void loop() {
  for (int i = -400; i < 400; i++) {
    motor.speed(i);
    delay(10);
  }

  delay(100);

  for (int i = 400; i > -400; i--) {
    motor.speed(i);
    delay(10);
  }

  delay(100);
}