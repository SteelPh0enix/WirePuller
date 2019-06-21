#include "setmotorpowerrequest.h"
#include <QJsonDocument>
#include <QJsonObject>

void SetMotorPowerRequest::setAxisPower(const QString& axis, int power) {
  m_powers[axis] = power;
}

QByteArray SetMotorPowerRequest::data() const {
  QJsonObject obj;

  obj["Request"] = "SetPower";
  auto requestData = QJsonObject();

  for (auto it = m_powers.cbegin(); it != m_powers.cend(); it++) {
    requestData[it.key()] = it.value();
  }

  obj["Data"] = requestData;

  return QJsonDocument(obj).toJson();
}
