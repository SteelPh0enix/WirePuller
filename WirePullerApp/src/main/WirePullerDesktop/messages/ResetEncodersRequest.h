#ifndef RESETENCODERSREQUEST_H
#define RESETENCODERSREQUEST_H
#include "Message.h"
#include "RequestType.h"


class ResetEncodersRequest
{
public:
    RequestType getType() const;
    QJsonObject toObject() const;

    /**
     * @brief resetEncoder Sets true flag for encoderId to be reset
     * @param encoderId ID of the encoder
     */
    void resetEncoder(const QString &encoderId);


private:
    QJsonObject data;
};

#endif // RESETENCODERSREQUEST_H
