#include "setmotorpowerrequest.h"
#include <QJsonDocument>
#include <QJsonObject>

void SetMotorPowerRequest::setAxisPower(const QString& axis, int power) {
  m_powers[axis] = power;
}

QByteArray SetMotorPowerRequest::data() const {
  QJsonObject obj;

  return QJsonDocument(obj).toJson();
}
