#include "JsonAxisController.hpp"
#include <Constants.hpp>
#include <Pinout.hpp>

JsonAxisController::JsonAxisController() {
  // Motors
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

  // Endstops
  axisX.setEndstopsPins(Pin::XAxis::Endstop::Left, Pin::XAxis::Endstop::Right);
  axisWheel.setEndstopsPins(Pin::WheelAxis::Endstop::Left,
                            Pin::WheelAxis::Endstop::Right);
  axisBreaker.disableEndstops();

  axisX.setEndstopsPullups(true);
  axisWheel.setEndstopsPullups(true);

  axisX.setEndstopsInversion(true);
  axisWheel.setEndstopsInversion(true);

  // Additional check
  axisX.checkPinsInitialization();
  axisWheel.checkPinsInitialization();
  axisBreaker.checkPinsInitialization();
}

void JsonAxisController::parseJsonInput(ArduinoJson::JsonDocument const& input,
                                        ArduinoJson::JsonDocument& output) {
  char const* requestType = input[Constant::Json::Key::RequestType].as<char const*>();

  if (requestType == NULL) {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::NoRequestType;
    return;
  }

  auto inputData =
      input[Constant::Json::Key::RequestData].as<ArduinoJson::JsonObjectConst>();
  if (inputData.isNull()) {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::NoData;
    return;
  }

  if (strcmp(requestType, Constant::Json::Value::RequestType::Callibrate) == 0) {
    commandCallibrate(inputData, output);
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::SetPower) == 0) {
    commandSetPower(inputData, output);
  } else if (strcmp(requestType, Constant::Json::Value::RequestType::GetData) == 0) {
    commandGetData(inputData, output);
  } else {
    output[Constant::Json::Key::RequestError] =
        Constant::Json::Value::RequestError::InvalidRequestType;
  }
}

bool JsonAxisController::initialize() {
  return axisX.initialize() && axisWheel.initialize() && axisBreaker.initialize();
}

void JsonAxisController::safetyEndstopCheck() {
  axisX.stopOnEndstopHit();
  axisWheel.stopOnEndstopHit();
  axisBreaker.stopOnEndstopHit();
}

void JsonAxisController::commandCallibrate(ArduinoJson::JsonObjectConst data,
                                           ArduinoJson::JsonDocument& output) {}

void JsonAxisController::commandSetPower(ArduinoJson::JsonObjectConst data,
                                         ArduinoJson::JsonDocument& output) {}

void JsonAxisController::commandGetData(ArduinoJson::JsonObjectConst data,
                                        ArduinoJson::JsonDocument& output) {}