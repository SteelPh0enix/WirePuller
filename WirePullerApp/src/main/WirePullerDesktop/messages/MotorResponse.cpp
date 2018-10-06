#include "MotorResponse.h"


constexpr char MotorResponse::RESPONSE_OBJECT[];

QList<QString> MotorResponse::getMotorIds() const
{
    return motors.keys();
}

MotorResponse::MotorData MotorResponse::getData(const QString &motorId) const
{
    auto motorData = motors.value(motorId).toObject();
    return MotorData {
        motorData.value("error").toBool(),
        motorData.value("speed").toInt(),
        motorData.value("current").toInt()
    };
}

MotorResponse MotorResponse::fromJson(const QJsonObject &object)
{
    MotorResponse motorResponse;
    motorResponse.motors = object;
    return motorResponse;
}

bool operator==(const MotorResponse::MotorData &lhs, const MotorResponse::MotorData &rhs)
{
    return lhs.error == rhs.error
            && lhs.speed == rhs.speed
            && lhs.current == rhs.current;
}
