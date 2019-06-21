#ifndef SETMOTORPOWERREQUEST_H
#define SETMOTORPOWERREQUEST_H
#include "request.h"
#include <QMap>
#include <QString>

class SetMotorPowerRequest : public Request {
 public:
  void setAxisPower(QString const& axis, int power);

  virtual QByteArray data() const override;

 private:
  QMap<QString, int> m_powers{};
};

#endif // SETMOTORPOWERREQUEST_H
