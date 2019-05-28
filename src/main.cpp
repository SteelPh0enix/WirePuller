#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <Constants.hpp>
#include "JsonAxisController.hpp"

ArduinoJson::StaticJsonDocument<Constant::Json::DocumentSize> jsonInputDoc{};
ArduinoJson::StaticJsonDocument<Constant::Json::DocumentSize> jsonOutputDoc{};

void printError(ArduinoJson::DeserializationError const& error) {
  jsonOutputDoc[Constant::Json::Key::ParsingError] = error.c_str();
  ArduinoJson::serializeJson(jsonOutputDoc, Serial);
}

void setup() { Serial.begin(Constant::Serial::BaudRate); }

void loop() {
  if (Serial.available()) {
    char inputBuffer[Constant::Json::DocumentSize]{};
    Serial.readBytesUntil(Constant::Serial::LineTerminator, inputBuffer,
                          Constant::Json::DocumentSize);

    ArduinoJson::DeserializationError inputDeserializationResult =
        ArduinoJson::deserializeJson(jsonInputDoc, inputBuffer);

    if (inputDeserializationResult == ArduinoJson::DeserializationError::Ok) {
      JsonAxisController::parseJsonInput(jsonInputDoc, jsonOutputDoc);
      ArduinoJson::serializeJson(jsonOutputDoc, Serial);
    } else {
      printError(inputDeserializationResult);
    }

    jsonInputDoc.clear();
    jsonOutputDoc.clear();
  }
}