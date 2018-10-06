#include "EncoderResponse.h"

constexpr char EncoderResponse::RESPONSE_OBJECT[];

EncoderResponse EncoderResponse::fromJson(const QJsonObject &obj)
{
    EncoderResponse encoderResponse;
    encoderResponse.encoders = obj;
    return encoderResponse;
}

int EncoderResponse::getPosition(const QString &encoderId) const
{
    return encoders.value(encoderId).toInt();
}
