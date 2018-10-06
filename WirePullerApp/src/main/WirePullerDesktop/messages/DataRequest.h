#ifndef DATAREQUEST_H
#define DATAREQUEST_H
#include "Message.h"
#include "RequestType.h"


enum class DataFlag
{
    ALL = 0,
    MOTOR = 1,
    ENDSTOP = 2,
    ENCODER = 4
};

class DataRequest : public Message<DataRequest>
{
public:
    RequestType getType() const;
    QJsonObject toObject() const;

    void setFlag(DataFlag flag);


private:
    DataFlag flag {DataFlag::ALL};
};

#endif // DATAREQUEST_H
