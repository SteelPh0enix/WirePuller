#ifndef ENCODERRESPONSE_H
#define ENCODERRESPONSE_H
#include <QJsonObject>


class EncoderResponse
{
public:
    static constexpr char RESPONSE_OBJECT[] = "encoders";
    static EncoderResponse fromJson(const QJsonObject &obj);

    int getPosition(const QString &encoderId) const;

private:
    QJsonObject encoders;
};

#endif // ENCODERRESPONSE_H
