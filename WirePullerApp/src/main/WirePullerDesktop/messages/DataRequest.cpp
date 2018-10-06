#include "DataRequest.h"


RequestType DataRequest::getType() const
{
    return  RequestType::GET_DATA;
}

QJsonObject DataRequest::toObject() const
{
    QJsonObject data;
    data["flag"] = static_cast<int>(flag);
    return data;
}

void DataRequest::setFlag(DataFlag flag)
{
    this->flag = flag;
}
