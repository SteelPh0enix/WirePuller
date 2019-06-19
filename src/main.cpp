#include <Arduino.h>
#include <ArduinoJson.hpp>
#include <Constants.hpp>
#include "JsonAxisController.hpp"

ArduinoJson::StaticJsonDocument<Constant::Json::DocumentSize> jsonInputDoc{};
ArduinoJson::StaticJsonDocument<Constant::Json::DocumentSize> jsonOutputDoc{};
JsonAxisController controller;

void printParsingError(ArduinoJson::DeserializationError const& error,
                       ArduinoJson::JsonDocument& json) {
  json[Constant::Json::Key::ParsingError] = error.c_str();
  ArduinoJson::serializeJson(json, Serial);
}

void setup() {
  Serial.begin(Constant::Serial::BaudRate);
  controller.setPins();
  if (!controller.initialize()) {
    jsonOutputDoc[Constant::Json::Key::GeneralError] =
        Constant::Json::Value::GeneralError::InitializationFailed;
    ArduinoJson::serializeJson(jsonOutputDoc, Serial);

    pinMode(LED_BUILTIN, OUTPUT);
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
}

void loop() {
  if (Serial.available()) {
    char inputBuffer[Constant::Json::DocumentSize]{};
    Serial.readBytesUntil(Constant::Serial::LineTerminator, inputBuffer,
                          Constant::Json::DocumentSize);

    ArduinoJson::DeserializationError inputDeserializationResult =
        ArduinoJson::deserializeJson(jsonInputDoc, inputBuffer);

    if (inputDeserializationResult == ArduinoJson::DeserializationError::Ok) {
      controller.parseJsonInput(jsonInputDoc, jsonOutputDoc);
      ArduinoJson::serializeJson(jsonOutputDoc, Serial);
    } else {
      printParsingError(inputDeserializationResult, jsonOutputDoc);
    }

    Serial.println();
    jsonInputDoc.clear();
    jsonOutputDoc.clear();
  }

  controller.safetyEndstopCheck();
}