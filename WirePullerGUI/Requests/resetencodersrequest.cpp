#include "resetencodersrequest.h"
#include <QJsonDocument>
#include <QJsonObject>

void ResetEncodersRequest::setAxisResetState(const QString& axis, bool state) {
  if (state) {
    m_resetStates[axis] = state;
  } else {
    m_resetStates.remove(axis);
  }
}

QByteArray ResetEncodersRequest::data() const {
  QJsonObject obj;

  obj["Request"] = "GetReset";
  auto requestData = QJsonObject();

  for (auto it = m_resetStates.cbegin(); it != m_resetStates.cend(); it++) {
    requestData[it.key()] = it.value();
  }

  obj["Data"] = requestData;

  return QJsonDocument(obj).toJson();
}
