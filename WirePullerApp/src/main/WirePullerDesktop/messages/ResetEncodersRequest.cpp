#include "ResetEncodersRequest.h"


RequestType ResetEncodersRequest::getType() const
{
    return RequestType::RESET_ENCODER;
}

QJsonObject ResetEncodersRequest::toObject() const
{
    return data;
}

void ResetEncodersRequest::resetEncoder(const QString &encoderId)
{
    data[encoderId] = true;
}
