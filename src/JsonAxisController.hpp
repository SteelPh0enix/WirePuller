#pragma once

#include <ArduinoJson.hpp>

namespace JsonAxisController {
void parseJsonInput(ArduinoJson::JsonDocument const& input,
                    ArduinoJson::JsonDocument& output);
}