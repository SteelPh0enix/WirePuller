#ifndef MOTORSPEEDMESSAGE_H
#define MOTORSPEEDMESSAGE_H
#include "Message.h"
#include "RequestType.h"

/**
 * @brief The MotorSpeedMessage class encapsulates a command to set desired motor speed
 */
class MotorSpeedRequest : public Message<MotorSpeedRequest>
{
public:
    RequestType getType() const;
    QJsonObject toObject() const;

    /**
     * @brief setMotorSpeed Sets motor speed
     * @param motorId ID of the motor
     * @param value value in range of [-400, 400]
     */
    void setMotorSpeed(const QString &motorId, int value);


private:
    QJsonObject data;
};

#endif // MOTORSPEEDMESSAGE_H
