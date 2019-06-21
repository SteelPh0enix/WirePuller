#include "getdatarequest.h"
#include <QJsonDocument>
#include <QJsonObject>

QByteArray GetDataRequest::data() const {
  QJsonObject obj;
  obj["Request"] = "GetData";
  obj["Data"] = QJsonObject();

  return QJsonDocument(obj).toJson();
}
