#include <Arduino.h>
#include <Constants.hpp>
#include <Endstop.hpp>

constexpr uint8_t EndstopPin{};
constexpr unsigned long WaitTime{10};

Endstop endstop(EndstopPin);
bool oldValue{false};

void test_endstop_initialization(Endstop& endstop) {
  Serial.print("Endstop initialization... ");
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