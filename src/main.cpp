#include <Arduino.h>
#include <Constants.hpp>
#include <Endstop.hpp>
#include <Pinout.hpp>

constexpr uint8_t EndstopPin{Pin::WheelAxis::Endstop::Right};
constexpr unsigned long WaitTime{10};

Endstop endstop(EndstopPin);
bool oldValue{false};

void test_endstop_initialization(Endstop& endstop) {
  Serial.print("Endstop initialization... ");
  endstop.setPullup(true);
  endstop.setOutputInversion(true);
  Serial.println(endstop.initialize() ? "OK" : "FAILED");
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  test_endstop_initialization(endstop);
  Serial.print("Default state: ");
  Serial.println(oldValue);
}

void loop() {
  bool readValue = endstop.read();
  if (oldValue != readValue) {
    oldValue = readValue;
    Serial.print("New state: ");
    Serial.println(readValue);
  }
  delay(WaitTime);
}