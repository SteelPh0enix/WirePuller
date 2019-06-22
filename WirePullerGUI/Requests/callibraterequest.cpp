#include "callibraterequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray CallibrateRequest::data() const {
  QJsonObject data;
  data["Request"] = "Callibrate";
  data["Data"] = QJsonObject();

  return QJsonDocument(data).toJson(QJsonDocument::Compact);
}
