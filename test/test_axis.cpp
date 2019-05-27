#include <Arduino.h>
#include <stdio.h>
#include <Axis.hpp>
#include <Constants.hpp>

constexpr uint8_t EncoderPinA{};
constexpr uint8_t EncoderPinB{};

constexpr uint8_t EndstopLeftPin{};
constexpr uint8_t EndstopRightPin{};

constexpr uint8_t MotorPWMPin{};
constexpr uint8_t MotorDirectionPin{};
constexpr uint8_t MotorFeedbackPin{};
constexpr uint8_t MotorDisablePin{};
constexpr uint8_t MotorStatusFlagPin{};

constexpr int PowerLimit{100};
constexpr long SleepTime{100};

bool feedbackEnabled{true};

Axis<EncoderPinA, EncoderPinB> axis;

void test_axis_initialization() {
  axis.setEndstopsPins(EndstopLeftPin, EndstopRightPin);
  axis.setMotorDriverPins(MotorPWMPin, MotorDirectionPin, MotorFeedbackPin,
                          MotorDisablePin, MotorStatusFlagPin);

  Serial.print("Axis initialization... ");
  Serial.println(axis.initialize() ? "OK" : "FAILED");
}

void print_axis_feedback() {
  char buffer[256]{};
  sprintf(buffer,
          "Axis feedback:\n   Motor power: %d\n   Motor current: %lf\n   Motor "
          "error: %d\n   Endstop states: %d\n   Encoder reading: %ld",
          axis.motorPower(), axis.motorCurrent(), axis.motorError(),
          static_cast<int>(axis.endstopStates()), axis.encoderValue());

  Serial.println(buffer);
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  Serial.println("Beginning axis test...");
  test_axis_initialization();
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    switch (command) {
      case 'l': {
        axis.setMotorPower(-PowerLimit);
      }
      case 'r': {
        axis.setMotorPower(PowerLimit);
      }
      case 's': {
        axis.setMotorPower(0);
      }
      case 'f': {
        feedbackEnabled = !feedbackEnabled;
      }
    }
  }

  if (feedbackEnabled) {
    print_axis_feedback();
  }

  delay(SleepTime);
}