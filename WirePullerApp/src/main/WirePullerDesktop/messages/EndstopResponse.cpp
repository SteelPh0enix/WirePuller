#include "EndstopResponse.h"


constexpr char EndstopResponse::RESPONSE_OBJECT[];

EndstopResponse EndstopResponse::fromJson(const QJsonObject &object)
{
    EndstopResponse endstops;
    endstops.endstops = object;
    return endstops;
}

bool EndstopResponse::getState(const QString &endstopId) const
{
    return this->endstops.value(endstopId).toBool();
}
