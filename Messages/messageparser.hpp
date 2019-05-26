#ifndef MESSAGEPARSER_HPP
#define MESSAGEPARSER_HPP

#include <QByteArray>
#include "wirepullerrequest.hpp"
#include "wirepullerresponse.hpp"

class MessageParser {
 public:
  virtual ~MessageParser() = default;
  virtual QByteArray parseRequest(Request const& request) const = 0;
  virtual Response parseResponse(
      QByteArray const& response) const = 0;
};

#endif  // MESSAGEPARSER_HPP
