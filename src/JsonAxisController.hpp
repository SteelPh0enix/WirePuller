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
  Axis<Pin::XAxis::Encoder::A, Pin::XAxis::Encoder::B> axisX{};
  Axis<Pin::WheelAxis::Encoder::A, Pin::WheelAxis::Encoder::B> axisWheel{};
  Axis<Pin::BreakerAxis::Encoder::A, Pin::BreakerAxis::Encoder::B> axisBreaker{};

  void commandCallibrate(ArduinoJson::JsonObjectConst data,
                         ArduinoJson::JsonDocument& output);
  void commandSetPower(ArduinoJson::JsonObjectConst data,
                       ArduinoJson::JsonDocument& output);
  void commandGetData(ArduinoJson::JsonObjectConst data,
                      ArduinoJson::JsonDocument& output);
};