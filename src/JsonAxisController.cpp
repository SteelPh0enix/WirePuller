#include "JsonAxisController.hpp"
#include <Constants.hpp>

JsonAxisController::JsonAxisController() {}

void JsonAxisController::parseJsonInput(ArduinoJson::JsonDocument const& input,
                                        ArduinoJson::JsonDocument& output) {
  char const* requestType = input[Constant::Json::Key::RequestType].as<char const*>();

  if (requestType == NULL) {
    output[Constant::Json::Key::RequestError] = Constant::Json::Value::RequestError::NoRequestType;
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::Callibrate) == 0) {
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::SetPower) == 0) {
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::GetData) == 0) {
  } else {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::InvalidRequestType;
  }
}

bool JsonAxisController::initialize() {}