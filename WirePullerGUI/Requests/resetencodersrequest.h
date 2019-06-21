#ifndef RESETENCODERSREQUEST_H
#define RESETENCODERSREQUEST_H
#include "request.h"
#include <QMap>
#include <QString>

class ResetEncodersRequest : public Request {
 public:
  void setAxisResetState(QString const& axis, bool state);

  virtual QByteArray data() const override;

 private:
  QMap<QString, bool> m_resetStates{};
};

#endif // RESETENCODERSREQUEST_H
