#include "requestbuilder.hpp"
#include <algorithm>
#include "jsonconstants.hpp"

Request RequestBuilder::makeSetMotorSpeedRequest(
    QHash<QString, int> const& motorList) {
  Request request{};

  request.type = Message::RequestType::SetMotorSpeed;

  for (auto motor = motorList.cbegin(); motor != motorList.cend(); motor++) {
    request.data[motor.key()] = motor.value();
  }

  return request;
}

Request RequestBuilder::makeGetDataRequest(Message::DataFlag const& dataType) {
  Request request{};

  request.type = Message::RequestType::GetData;
  request.data.insert(JsonKey::DataRequestFlag, static_cast<int>(dataType));

  return request;
}

Request RequestBuilder::makeResetEncoderRequest(
    QHash<QString, bool> const& encodersList) {
  Request request{};

  request.type = Message::RequestType::ResetEncoder;
  for (auto encoder = encodersList.cbegin(); encoder != encodersList.cend();
       encoder++) {
    request.data[encoder.key()] = encoder.value();
  }

  return request;
}
