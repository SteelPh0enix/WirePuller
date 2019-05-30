#include "JsonAxisController.hpp"
#include <Constants.hpp>
#include <Pinout.hpp>

namespace {
namespace JsonKey = Constant::Json::Key;
namespace JsonValue = Constant::Json::Value;
}  // namespace

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
  char const* requestType = input[JsonKey::RequestType].as<char const*>();

  if (requestType == NULL) {
    output[JsonKey::RequestError] = JsonValue::RequestError::NoRequestType;
    return;
  }

  auto inputData = input[JsonKey::RequestData].as<ArduinoJson::JsonObjectConst>();
  if (inputData.isNull()) {
    output[JsonKey::RequestError] = JsonValue::RequestError::NoData;
    return;
  }

  if (strcmp(requestType, JsonValue::RequestType::Callibrate) == 0) {
    commandCallibrate(inputData, output);
  } else if (strcmp(requestType, JsonValue::RequestType::SetPower) == 0) {
    commandSetPower(inputData, output);
  } else if (strcmp(requestType, JsonValue::RequestType::GetData) == 0) {
    commandGetData(inputData, output);
  } else if (strcmp(requestType, JsonValue::RequestType::ResetEncoder) == 0) {
    commandResetEncoder(inputData, output);
  } else {
    output[JsonKey::RequestError] = JsonValue::RequestError::InvalidRequestType;
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
                                           ArduinoJson::JsonDocument& output) {
  if (axisX.endstopsEnabled()) {
    axisX.callibrate(AxisX::EndstopsState::Right);
  }
  if (axisWheel.endstopsEnabled()) {
    axisWheel.callibrate(AxisWheel::EndstopsState::Left);
  }
  if (axisBreaker.endstopsEnabled()) {
    axisBreaker.callibrate(AxisBreaker::EndstopsState::Right);
  }

  output[JsonKey::Callibration] = JsonValue::OK;
  fillOutputWithAxisData(output);
}

void JsonAxisController::commandSetPower(ArduinoJson::JsonObjectConst data,
                                         ArduinoJson::JsonDocument& output) {
  if (!data[JsonKey::AxisName::X].isNull()) {
    axisX.setMotorPower(data[JsonKey::AxisName::X].as<int>());
  }
  if (!data[JsonKey::AxisName::Wheel].isNull()) {
    axisWheel.setMotorPower(data[JsonKey::AxisName::Wheel].as<int>());
  }
  if (!data[JsonKey::AxisName::Breaker].isNull()) {
    axisBreaker.setMotorPower(data[JsonKey::AxisName::Breaker].as<int>());
  }

  fillOutputWithAxisData(output);
}

void JsonAxisController::commandGetData(ArduinoJson::JsonObjectConst data,
                                        ArduinoJson::JsonDocument& output) {
  fillOutputWithAxisData(output);
}

void JsonAxisController::commandResetEncoder(ArduinoJson::JsonObjectConst data,
                                             ArduinoJson::JsonDocument& output) {
  if (!data[JsonKey::AxisName::X].isNull()) {
    axisX.resetEncoderValue();
  }
  if (!data[JsonKey::AxisName::Wheel].isNull()) {
    axisWheel.resetEncoderValue();
  }
  if (!data[JsonKey::AxisName::Breaker].isNull()) {
    axisBreaker.resetEncoderValue();
  }

  fillOutputWithAxisData(output);
}

void JsonAxisController::fillOutputWithAxisData(ArduinoJson::JsonDocument& output) {
  fillJsonObjectWithAxisData(output.createNestedObject(JsonKey::AxisName::X), axisX);
  fillJsonObjectWithAxisData(output.createNestedObject(JsonKey::AxisName::Wheel),
                             axisWheel);
  fillJsonObjectWithAxisData(output.createNestedObject(JsonKey::AxisName::Breaker),
                             axisBreaker);
}
