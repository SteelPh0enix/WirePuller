#include "jsonmessageparser.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include "devicenames.hpp"
#include "jsonconstants.hpp"

QByteArray JsonMessageParser::parseRequest(Request const& request) const {
  QJsonObject json{};

  json[JsonKey::Type] = convertRequestTypeToString(request.type);
  json[JsonKey::Data] = convertRequestDataToJson(request);

  return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Response JsonMessageParser::parseResponse(QByteArray const& rawResponse) const {
  QJsonParseError error{};
  Response response{};

  auto responseJson = QJsonDocument::fromJson(rawResponse, &error);

  if (error.error != QJsonParseError::NoError) {
    response.type = Message::ResponseType::Invalid;
    response.data["reason"] = error.errorString();

    return response;
  }

  response.type =
      convertStringToResponseType(responseJson[JsonKey::Type].toString());

  response.data =
      convertDataJsonToResponseData(responseJson[JsonKey::Data].toObject());

  return response;
}

QString JsonMessageParser::convertRequestTypeToString(
    Message::RequestType type) const {
  switch (type) {
    case Message::RequestType::Invalid: {
      return "invalid";
    }
    case Message::RequestType::SetMotorSpeed: {
      return JsonValue::RequestType::SetMotorSpeed;
    }
    case Message::RequestType::GetData: {
      return JsonValue::RequestType::GetData;
    }
    case Message::RequestType::ResetEncoder: {
      return JsonValue::RequestType::ResetEncoder;
    }
  }
  return QString();
}

QString JsonMessageParser::convertResponseTypeToString(
    Message::ResponseType type) const {
  switch (type) {
    case Message::ResponseType::Invalid: {
      return "invalid";
    }
    case Message::ResponseType::Data: {
      return JsonValue::ResponseType::Data;
    }
    case Message::ResponseType::Error: {
      return JsonValue::ResponseType::Error;
    }
  }
  return QString();
}

QJsonObject JsonMessageParser::convertRequestDataToJson(
    Request const& request) const {
  QJsonObject json{};
  switch (request.type) {
    case Message::RequestType::Invalid: {
      break;
    }
    case Message::RequestType::SetMotorSpeed: {
      for (auto motor = request.data.cbegin(); motor != request.data.cend();
           motor++) {
        json[motor.key()] = motor.value().toInt();
      }
      break;
    }
    case Message::RequestType::GetData: {
      json[JsonKey::DataRequestFlag] =
          request.data[JsonKey::DataRequestFlag].toInt();
      break;
    }
    case Message::RequestType::ResetEncoder: {
      for (auto encoder = request.data.cbegin(); encoder != request.data.cend();
           encoder++) {
        json[encoder.key()] = encoder.value().toBool();
      }
      break;
    }
  }
  return json;
}

Message::ResponseType JsonMessageParser::convertStringToResponseType(
    const QString& type) const {
  if (type == JsonValue::ResponseType::Data) {
    return Message::ResponseType::Data;
  } else if (type == JsonValue::ResponseType::Error) {
    return Message::ResponseType::Error;
  }
  return Message::ResponseType::Invalid;
}

ResponseData JsonMessageParser::convertDataJsonToResponseData(
    const QJsonObject& data) const {
  return data.toVariantHash();
}
