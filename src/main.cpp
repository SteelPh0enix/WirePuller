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

Axis<EncoderPinA, EncoderPinB> axis;

void test_axis_initialization() {
  axis.setEndstopsPins(EndstopLeftPin, EndstopRightPin);
  axis.setMotorDriverPins(MotorPWMPin, MotorDirectionPin, MotorFeedbackPin,
                          MotorDisablePin, MotorStatusFlagPin);

  Serial.print("Axis initialization... ");
  Serial.println(axis.initialize() ? "OK" : "FAILED");
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  Serial.println("Beginning axis test...");
  test_axis_initialization();
}

void loop() {}