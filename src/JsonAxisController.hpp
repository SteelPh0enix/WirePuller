#pragma once
#include <ArduinoJson.hpp>
#include <Axis.hpp>
#include <Constants.hpp>
#include <Pinout.hpp>

class JsonAxisController {
 public:
  JsonAxisController() = default;
  void setPins();
  void parseJsonInput(ArduinoJson::JsonDocument const& input,
                      ArduinoJson::JsonDocument& output);

  bool initialize();

  void safetyEndstopCheck();

 private:
  using AxisX = Axis<Pin::XAxis::Encoder::A, Pin::XAxis::Encoder::B>;
  using AxisWheel = Axis<Pin::WheelAxis::Encoder::A, Pin::WheelAxis::Encoder::B>;
  using AxisBreaker = Axis<Pin::BreakerAxis::Encoder::A, Pin::BreakerAxis::Encoder::B>;

  AxisX axisX{};
  AxisWheel axisWheel{};
  AxisBreaker axisBreaker{};

  void commandCallibrate(ArduinoJson::JsonObjectConst data,
                         ArduinoJson::JsonDocument& output);
  void commandSetPower(ArduinoJson::JsonObjectConst data,
                       ArduinoJson::JsonDocument& output);
  void commandGetData(ArduinoJson::JsonObjectConst data,
                      ArduinoJson::JsonDocument& output);
  void commandResetEncoder(ArduinoJson::JsonObjectConst data,
                           ArduinoJson::JsonDocument& output);

  void fillOutputWithAxisData(ArduinoJson::JsonDocument& output);

  template <typename AxisT>
  void setAxisPower(int power, AxisT& axis) {
    if (axis.endstopsEnabled() &&
        ((axis.leftEndstopHit() && power < 0) || (axis.rightEndstopHit() && power > 0) ||
         axis.bothEndstopsHit())) {
      return;
    }

    axis.setMotorPower(power);
  }

  template <typename AxisT>
  void fillJsonObjectWithAxisData(ArduinoJson::JsonObject object, AxisT& axis) {
    object[Constant::Json::Key::Motor::Power] = axis.motorPower();
    object[Constant::Json::Key::Motor::Current] = axis.motorCurrent();
    object[Constant::Json::Key::Motor::Error] = axis.motorError();
    auto endstopsState = axis.endstopsState();
    object[Constant::Json::Key::EndstopLeft] =
        static_cast<uint8_t>(endstopsState) &
                static_cast<uint8_t>(AxisT::EndstopsState::Left)
            ? true
            : false;
    object[Constant::Json::Key::EndstopRight] =
        static_cast<uint8_t>(endstopsState) &
                static_cast<uint8_t>(AxisT::EndstopsState::Right)
            ? true
            : false;
    object[Constant::Json::Key::EncoderTicks] = axis.encoderValue();
  }
};