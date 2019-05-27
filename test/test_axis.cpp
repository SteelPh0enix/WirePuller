#include <Arduino.h>
#include <stdio.h>
#include <Axis.hpp>
#include <Constants.hpp>
#include <Pinout.hpp>

constexpr uint8_t EncoderPinA{Pin::XAxis::Encoder::A};
constexpr uint8_t EncoderPinB{Pin::XAxis::Encoder::B};

constexpr uint8_t EndstopLeftPin{Pin::XAxis::Endstop::Left};
constexpr uint8_t EndstopRightPin{Pin::XAxis::Endstop::Right};

constexpr uint8_t MotorPWMPin{Pin::XAxis::MotorDriver::PWM};
constexpr uint8_t MotorDirectionPin{Pin::XAxis::MotorDriver::Direction};
constexpr uint8_t MotorFeedbackPin{Pin::XAxis::MotorDriver::Feedback};
constexpr uint8_t MotorDisablePin{Pin::XAxis::MotorDriver::Disable};
constexpr uint8_t MotorStatusFlagPin{Pin::XAxis::MotorDriver::StatusFlag};

constexpr int PowerLimit{150};
constexpr long SleepTime{500};

Axis<EncoderPinA, EncoderPinB> axis;

void test_axis_initialization() {
  axis.setEndstopsPins(EndstopLeftPin, EndstopRightPin);
  axis.setMotorDriverPins(MotorPWMPin, MotorDirectionPin, MotorFeedbackPin,
                          MotorDisablePin, MotorStatusFlagPin);
  axis.setEndstopsInversion(true);
  axis.setEndstopsPullups(true);

  Serial.print("Axis initialization... ");
  Serial.println(axis.initialize() ? "OK" : "FAILED");
}

void print_axis_feedback() {
  Serial.println("Axis feedback:");
  Serial.print("   Motor power: ");
  Serial.println(axis.motorPower());
  Serial.print("   Motor current: ");
  Serial.println(axis.motorCurrent());
  Serial.print("   Motor error: ");
  Serial.println(axis.motorError() ? "YES" : "NO");
  Serial.print("   Endstop states: ");
  Serial.println(static_cast<int>(axis.endstopStates()));
  Serial.print("   Encoder reading: ");
  Serial.println(axis.encoderValue());
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
        Serial.println(axis.setMotorPower(-PowerLimit) ? "SET" : "ERROR");
        break;
      }
      case 'r': {
        Serial.println(axis.setMotorPower(PowerLimit) ? "SET" : "ERROR");
        break;
      }
      case 's': {
        axis.setMotorPower(0);
        break;
      }
      case 'f': {
        print_axis_feedback();
        break;
      }
    }
  }

  delay(SleepTime);
}