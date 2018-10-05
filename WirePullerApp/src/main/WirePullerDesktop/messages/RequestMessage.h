#ifndef REQUESTMESSAGE_H
#define REQUESTMESSAGE_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QString>


template<class CRTP>
class Message
{
public:
    /**
     * @brief toJson Generates JSON to be transfered
     * @param pretty True if the JSON should be indented
     * @return A serialized JSON messaged
     */
    QByteArray toJson(bool pretty = false) const;

    /**
     * @brief toString Prints pretty JSON
     * @return Pretty JSON
     */
    QString toString() const;
};


enum class RequestType
{
    SET_MOTOR_SPEED,
    GET_DATA,
    RESET_ENCODER
};
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
        setData(dataObject.toObject());
    }

protected:
    QJsonObject toObject() const;


private:
    QString type;
    QJsonObject data;
};


/**
 * @brief The MotorSpeedMessage class encapsulates a command to set desired motor speed
 */
class MotorSpeedMessage : public Message<MotorSpeedMessage>
{
public:
    QJsonObject toObject() const;

    /**
     * @brief setMotorSpeed Sets motor speed
     * @param motorId ID of the motor
     * @param value value in range of [-400, 400]
     */
    void setMotorSpeed(const QString &motorId, int value);


private:
    QJsonObject data;
};


template<class CRTP>
QByteArray Message<CRTP>::toJson(bool pretty) const
{
    const CRTP &derived = static_cast<const CRTP&>(*this);
    return QJsonDocument(derived.toObject()).toJson(
                pretty ? QJsonDocument::Indented : QJsonDocument::Compact);
}

template<class CRTP>
QString Message<CRTP>::toString() const
{
    return QString(toJson(true));
}
#endif // REQUESTMESSAGE_H
