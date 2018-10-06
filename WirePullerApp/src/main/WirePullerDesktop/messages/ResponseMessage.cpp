#include "ResponseMessage.h"
#include <QJsonDocument>
#include <QDebug>

#include <unordered_map>
#include <string>

constexpr char ResponseMessage::ERROR[];
constexpr char ResponseMessage::DATA[];


namespace
{
const std::unordered_map<std::string, ResponseObject> TYPES = {
    {"motors",   ResponseObject::MOTORS},
    {"endstops", ResponseObject::ENDSTOPS},
    {"encoders", ResponseObject::ENCODERS}
};
}

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

ResponseObject ResponseMessage::getResponseObject(const QString &objectType)
{
    try
    {
        return TYPES.at(objectType.toStdString());
    }
    catch (std::out_of_range &e)
    {
        qDebug() << "Cannot retrieve response object type:" << e.what();
        return ResponseObject::UNKNOWN;
    }
}
