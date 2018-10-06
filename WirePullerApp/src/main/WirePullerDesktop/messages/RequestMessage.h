#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QString>

#include "Message.h"
#include "RequestType.h"

/**
 * @brief The RequestMessage class encapsulates messages content
 *
 * RequestMessage encapsulates the following JSON pattern:
 *
   {
    "type": "type",
    "data": {
        "field": object/value,
        "field": object/value
   }
 *
 * "type" - mandatory
 * "data" - a generic contianer for any of parameters to be serialized
}
 */
class RequestMessage : public Message<RequestMessage>
{
    friend class Message<RequestMessage>;
public:

    /**
     * @brief setType Sets a type of a message
     * @param type RequestType type
     */
    void setType(RequestType type);

    /**
     * @brief setType Sets a type that is a special case, not available in enum
     * @param type Non-standard request type
     */
    void setType(const QString &type);

    /**
     * @brief setData Sets a custom message as 'data' message
     * @param data JSON['data'] value
     */
    void setData(QJsonObject &&data);

    /**
     * @brief setData Sets a predefined message as 'data' message
     * @param dataObject must contain toObject() : QJsonObject method
     */
    template<typename TO_JSON_OBJ>
    void setData(const TO_JSON_OBJ &dataObject)
    {
        setType(dataObject.getType());
        setData(dataObject.toObject());
    }

protected:
    QJsonObject toObject() const;


private:
    QString type;
    QJsonObject data;
};


#endif // REQUESTMESSAGE_H
