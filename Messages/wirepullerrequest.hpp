#ifndef WIREPULLERREQUEST_HPP
#define WIREPULLERREQUEST_HPP

#include <QVariantHash>
#include "messagetypes.hpp"

using RequestData = QVariantHash;

struct Request {
  Message::RequestType type;
  RequestData data;
};

#endif  // WIREPULLERREQUEST_HPP
