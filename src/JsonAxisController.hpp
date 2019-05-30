#pragma once
#include <ArduinoJson.hpp>
#include <Axis.hpp>
#include <Pinout.hpp>

class JsonAxisController {
 public:
  JsonAxisController();
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
};