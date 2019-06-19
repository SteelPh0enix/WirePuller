#include <Arduino.h>
#include <Encoder.h>
#include <stdint.h>
#include <Constants.hpp>
#include <MC33926.hpp>
#include <Pinout.hpp>

constexpr uint8_t EncoderPinA{Pin::BreakerAxis::Encoder::A};
constexpr uint8_t EncoderPinB{Pin::BreakerAxis::Encoder::B};
constexpr uint8_t PWMPin{Pin::BreakerAxis::MotorDriver::PWM};
constexpr uint8_t DirectionPin{Pin::BreakerAxis::MotorDriver::Direction};
constexpr uint8_t FeedbackPin{Pin::BreakerAxis::MotorDriver::Feedback};
constexpr uint8_t DisablePin{Pin::BreakerAxis::MotorDriver::Disable};
constexpr uint8_t StatusFlagPin{Pin::BreakerAxis::MotorDriver::StatusFlag};

MC33926 motor(PWMPin, DirectionPin, FeedbackPin, DisablePin, StatusFlagPin);

Encoder encoder(EncoderPinA, EncoderPinB);

void test_initialize_motor(MC33926& motor) {
  Serial.print("Initializing motor... ");
  Serial.println(motor.initialize() ? "OK" : "FAILED");
}

long oldPosition = -999;

void print_encoder_reading() {
  long newPosition = encoder.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  test_initialize_motor(motor);
  Serial.println("Starting encoder test...");
}

void loop() {
  motor.setPower(100);
  for(int i = 0; i < 50; i++) {
    print_encoder_reading();
    delay(100);
  }

  motor.setPower(-100);
  for(int i = 0; i < 50; i++) {
    print_encoder_reading();
    delay(100);
  }

  motor.setPower(0);
  print_encoder_reading();
  while(1) {
    delay(1000);
    print_encoder_reading();
  }
}