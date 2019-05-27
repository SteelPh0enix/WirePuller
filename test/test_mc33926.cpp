#include <Arduino.h>
#include <stdio.h>
#include <Constants.hpp>
#include <MC33926.hpp>
#include <Pinout.hpp>

constexpr uint8_t PWMPin{Pin::BreakerAxis::MotorDriver::PWM};
constexpr uint8_t DirectionPin{Pin::BreakerAxis::MotorDriver::Direction};
constexpr uint8_t FeedbackPin{Pin::BreakerAxis::MotorDriver::Feedback};
constexpr uint8_t DisablePin{Pin::BreakerAxis::MotorDriver::Disable};
constexpr uint8_t StatusFlagPin{Pin::BreakerAxis::MotorDriver::StatusFlag};

MC33926 motor(PWMPin, DirectionPin, FeedbackPin, DisablePin, StatusFlagPin);

void print_motor_data(MC33926 const& motor) {
  Serial.println("Motor data:");
  Serial.print("   Power: ");
  Serial.println(motor.power());
  Serial.print("   Current: ");
  Serial.println(motor.current());
  Serial.print("   Error: ");
  Serial.println(motor.error() ? "YES" : "NO");
}

void test_initialize_motor(MC33926& motor) {
  Serial.print("Initializing motor... ");
  Serial.println(motor.initialize() ? "OK" : "FAILED");
}

void test_motor_set_power(MC33926& motor, int step = 20,
                          unsigned long delayBetweenSteps = 100,
                          bool printData = true) {
  Serial.println("Powering up...");

  for (int power{0}; power < motor.maxPower(); power += step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
    delay(delayBetweenSteps);
  }

  Serial.println("Powering down and reversing...");

  for (int power{motor.maxPower()}; power > -motor.maxPower(); power -= step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
    delay(delayBetweenSteps);
  }

  Serial.println("Stopping...");
  for (int power{-motor.maxPower()}; power < 0; power += step) {
    motor.setPower(power);
    if (printData) {
      print_motor_data(motor);
    }
    delay(delayBetweenSteps);
  }

  motor.setPower(0);
  Serial.println("Test finished.");
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  test_initialize_motor(motor);
  print_motor_data(motor);
  delay(4000);
}

void loop() { test_motor_set_power(motor); 
delay(1000);}