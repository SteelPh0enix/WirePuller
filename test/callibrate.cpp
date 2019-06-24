#include <Arduino.h>
#include <Encoder.h>
#include <Constants.hpp>
#include <MC33926.hpp>
#include <Pinout.hpp>

namespace AxisPins = Pin::WheelAxis;
namespace MotorPin = AxisPins::MotorDriver;
namespace EncoderPin = AxisPins::Encoder;

constexpr int MinimalPower{35};
constexpr double TicksPerMillimeter{266.666};

MC33926 motor(MotorPin::PWM, MotorPin::Direction, MotorPin::Feedback, MotorPin::Disable,
              MotorPin::StatusFlag);
Encoder encoder(EncoderPin::A, EncoderPin::B);

double calculateSpeed(double encoderTicks) { return encoderTicks / TicksPerMillimeter; }

double callibrate(int power) {
  encoder.write(0);
  motor.setPower(power);
  delay(1000);
  return calculateSpeed(static_cast<double>(encoder.read()));
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  motor.initialize();
  Serial.println("Starting...");

  Serial.print("First speed @ ");
  Serial.print(MinimalPower);
  Serial.print(": ");
  Serial.println(callibrate(MinimalPower));

  for (int power = 50; power <= 250; power += 50) {
    Serial.print("Speed @ ");
    Serial.print(power);
    Serial.print(": ");
    Serial.println(callibrate(power));
  }

  motor.setPower(0);
}

void loop() {}

/*
X axis:
First speed @ 25: 0.11
Speed @ 50: 0.29
Speed @ 100: 0.67
Speed @ 150: 1.09
Speed @ 200: 1.49
Speed @ 250: 1.87

First speed @ 25: 0.05
Speed @ 50: 0.19
Speed @ 100: 0.46
Speed @ 150: 0.72
Speed @ 200: 0.98
Speed @ 250: 1.24

First speed @ 35: 0.09
Speed @ 50: 0.20
Speed @ 100: 0.51
Speed @ 150: 0.79
Speed @ 200: 1.08
Speed @ 250: 1.39
*/
