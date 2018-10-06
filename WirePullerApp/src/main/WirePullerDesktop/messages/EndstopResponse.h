#ifndef ENDSTOPRESPONSE_H
#define ENDSTOPRESPONSE_H
#include <QJsonObject>


class EndstopResponse
{
public:
    static constexpr char RESPONSE_OBJECT[] = "endstops";
    static EndstopResponse fromJson(const QJsonObject &object);

    bool getState(const QString &endstopId) const;


private:
    QJsonObject endstops;
};

#endif // ENDSTOPRESPONSE_H
