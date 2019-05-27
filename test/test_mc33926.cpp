#include <Arduino.h>
#include <stdio.h>
#include <Constants.hpp>
#include <MC33926.hpp>

constexpr uint8_t PWMPin{};
constexpr uint8_t DirectionPin{};
constexpr uint8_t FeedbackPin{};
constexpr uint8_t DisablePin{};
constexpr uint8_t StatusFlagPin{};

MC33926 motor(PWMPin, DirectionPin, FeedbackPin, DisablePin, StatusFlagPin);

void print_motor_data(MC33926 const& motor) {
  char buffer[128]{};
  sprintf(buffer, "Motor data:\n  Power:%d\n  Current:%lf\n  Error: %d",
          motor.power(), motor.current(), motor.error());
  Serial.println(buffer);
}

void test_initialize_motor(MC33926& motor) {
  Serial.print("Initializing motor... ");
  Serial.println(motor.initialize() ? "OK" : "FAILED");
}

void test_motor_set_power(MC33926& motor, int step = 20,
                          unsigned long delayBetweenSteps = 5,
                          bool printData = true) {
  Serial.println("Powering up...");

  for (int power{0}; power < motor.maxPower(); power += step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
  }

  Serial.println("Powering down and reversing...");

  for (int power{motor.maxPower()}; power > -motor.maxPower(); power -= step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
  }

  Serial.println("Stopping...");
  for (int power{-motor.maxPower()}; power < 0; power += step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
  }

  motor.setPower(0);
  Serial.println("Test finished.");
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  test_initialize_motor(motor);
  print_motor_data(motor);
  delay(500);
}

void loop() { test_motor_set_power(motor); }