#ifndef WIREPULLERRESPONSE_HPP
#define WIREPULLERRESPONSE_HPP

#include <QVariantHash>
#include "messagetypes.hpp"

using ResponseData = QVariantHash;

struct Response {
  Message::ResponseType type;
  ResponseData data;
};

#endif  // WIREPULLERRESPONSE_HPP
