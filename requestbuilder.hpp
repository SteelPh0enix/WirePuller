#ifndef REQUESTBUILDER_HPP
#define REQUESTBUILDER_HPP

#include <QHash>
#include <QString>
#include "Messages/wirepullerrequest.hpp"
#include "devicenames.hpp"

class RequestBuilder {
 public:
  static Request makeSetMotorSpeedRequest(QHash<QString, int> const& motorList);

  static Request makeGetDataRequest(Message::DataFlag const& dataType);

  static Request makeResetEncoderRequest(
      QHash<QString, bool> const& encodersList);
};

#endif  // REQUESTBUILDER_HPP
