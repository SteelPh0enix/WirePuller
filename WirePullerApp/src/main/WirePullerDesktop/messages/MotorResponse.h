#ifndef MOTORRESPONSE_H
#define MOTORRESPONSE_H
#include <QJsonObject>
#include <QString>
#include <QList>


class MotorResponse
{
public:
    static constexpr char RESPONSE_OBJECT[] = "motors";
    struct MotorData
    {
        bool error;
        int speed;
        int current;
    };


    QList<QString> getMotorIds() const;
    MotorData getData(const QString &motorId) const;

    static MotorResponse fromJson(const QJsonObject &object);

    friend bool operator==(const MotorData &lhs, const MotorData &rhs);
private:
    QJsonObject motors;
};


#endif // MOTORRESPONSE_H
