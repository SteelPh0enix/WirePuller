#include "RequestMessage.h"
#include <QJsonDocument>
#include <QDebug>
#include <unordered_map>
#include <exception>


namespace
{
const std::unordered_map<RequestType, QString> TYPES = {
    {RequestType::SET_MOTOR_SPEED, "set_motor_speed"},
    {RequestType::GET_DATA, "data_request"},
    {RequestType::RESET_ENCODER, "reset_encoder"}
};
}


void RequestMessage::setType(RequestType type)
{
    try
    {
        this->type = TYPES.at(type);
    }
    catch (std::exception &e)
    {
        qDebug() << "Could not determine Request type: " << e.what();
    }
}

void RequestMessage::setType(const QString &type)
{
    this->type = type;
}

void RequestMessage::setData(QJsonObject &&data)
{
    this->data = std::move(data);
}

QJsonObject RequestMessage::toObject() const
{
    QJsonObject root;
    root["type"] = this->type;
    root["data"] = this->data;
    return root;
}
