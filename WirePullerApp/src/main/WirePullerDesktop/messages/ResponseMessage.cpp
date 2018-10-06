#include "ResponseMessage.h"
#include <QJsonDocument>

constexpr char ResponseMessage::ERROR[];
constexpr char ResponseMessage::DATA[];


ResponseMessage::ResponseMessage(const QByteArray &rawJson)
    : root(QJsonDocument::fromJson(rawJson).object())
{

}

ResponseType ResponseMessage::getType() const
{
    const QString type = root["type"].toString();
    ResponseType responseType {ResponseType::UNKNOWN};

    if (type == DATA)
    {
        responseType = ResponseType::DATA;
    }
    else if (type == ERROR)
    {
        responseType = ResponseType::ERROR;
    }

    return responseType;
}

bool ResponseMessage::contains(const QString &dataKey) const
{
    auto data {root.value("data").toObject()};
    return data.contains(dataKey);
}
