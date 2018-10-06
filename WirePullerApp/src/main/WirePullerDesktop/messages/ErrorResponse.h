#ifndef ERRORRESPONSE_H
#define ERRORRESPONSE_H
#include <QJsonObject>


class ErrorResponse
{
public:
    static constexpr char RESPONSE_OBJECT[] = "error";
    static ErrorResponse fromJson(const QJsonObject &obj);

    int getCode() const;
    QString getMessage() const;

private:
    QJsonObject error;
};

#endif // ERRORRESPONSE_H
