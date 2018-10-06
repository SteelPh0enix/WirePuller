#include "ErrorResponse.h"

constexpr char ErrorResponse::RESPONSE_OBJECT[];


ErrorResponse ErrorResponse::fromJson(const QJsonObject &obj)
{
    ErrorResponse errorResponse;
    errorResponse.error = obj;
    return errorResponse;
}

int ErrorResponse::getCode() const
{
    return error.value("code").toInt();
}

QString ErrorResponse::getMessage() const
{
    return error.value("message").toString();
}
