#include "JsonAxisController.hpp"
#include <Constants.hpp>
#include <Pinout.hpp>

JsonAxisController::JsonAxisController() {
  axisX.setMotorDriverPins(
      Pin::XAxis::MotorDriver::PWM, Pin::XAxis::MotorDriver::Direction,
      Pin::XAxis::MotorDriver::Feedback, Pin::XAxis::MotorDriver::Direction,
      Pin::XAxis::MotorDriver::StatusFlag);
  axisWheel.setMotorDriverPins(
      Pin::WheelAxis::MotorDriver::PWM, Pin::WheelAxis::MotorDriver::Direction,
      Pin::WheelAxis::MotorDriver::Feedback, Pin::WheelAxis::MotorDriver::Direction,
      Pin::WheelAxis::MotorDriver::StatusFlag);
  axisBreaker.setMotorDriverPins(
      Pin::BreakerAxis::MotorDriver::PWM, Pin::BreakerAxis::MotorDriver::Direction,
      Pin::BreakerAxis::MotorDriver::Feedback, Pin::BreakerAxis::MotorDriver::Direction,
      Pin::BreakerAxis::MotorDriver::StatusFlag);
}

void JsonAxisController::parseJsonInput(ArduinoJson::JsonDocument const& input,
                                        ArduinoJson::JsonDocument& output) {
  char const* requestType = input[Constant::Json::Key::RequestType].as<char const*>();

  if (requestType == NULL) {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::NoRequestType;
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::Callibrate) == 0) {
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::SetPower) == 0) {
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::GetData) == 0) {
  } else {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::InvalidRequestType;
  }
}

bool JsonAxisController::initialize() {
  return axisX.initialize() && axisWheel.initialize() && axisBreaker.initialize();
}
