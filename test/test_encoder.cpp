#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>
#include <Constants.hpp>

constexpr uint8_t EncoderPinA{};
constexpr uint8_t EncoderPinB{};

Encoder encoder(EncoderPinA, EncoderPinB);

long oldPosition = -999;

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  Serial.println("Starting encoder test...");
}

void loop() {
  long newPosition = encoder.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}