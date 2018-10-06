#include "MotorSpeedRequest.h"


RequestType MotorSpeedRequest::getType() const
{
    return RequestType::SET_MOTOR_SPEED;
}

QJsonObject MotorSpeedRequest::toObject() const
{
    return data;
}

void MotorSpeedRequest::setMotorSpeed(const QString &motorId, int value)
{
    constexpr auto MAX_SPEED {400};
    auto sign = value < 0 ? -1 : 1;
    value = std::abs(value) > MAX_SPEED ? sign * MAX_SPEED : value;

    data.insert(motorId, value);
}
