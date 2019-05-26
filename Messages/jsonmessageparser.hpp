#ifndef JSONMESSAGEPARSER_HPP
#define JSONMESSAGEPARSER_HPP

#include "messageparser.hpp"

class JsonMessageParser final : public MessageParser {
 public:
  virtual QByteArray parseRequest(Request const& request) const override;
  virtual Response parseResponse(QByteArray const& response) const override;

  QString convertRequestTypeToString(Message::RequestType type) const;
  QString convertResponseTypeToString(Message::ResponseType type) const;

  QJsonObject convertRequestDataToJson(Request const& request) const;

  Message::ResponseType convertStringToResponseType(QString const& type) const;
  ResponseData convertDataJsonToResponseData(QJsonObject const& data) const;
};

#endif  // JSONMESSAGEPARSER_HPP
