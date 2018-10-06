#ifndef RESPONSEMESSAGE_H
#define RESPONSEMESSAGE_H
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>

#include <exception>

#include "ResponseType.h"


/**
 * @brief The ResponseMessage class allows parsing serialized messages
 * and retrieve relevant data.
 */
class ResponseMessage
{
    static constexpr char ERROR[] = "error";
    static constexpr char DATA[] = "data";
public:
    /**
     * @brief ResponseMessage Parses raw JSON and thus allows accessing relevant
     * data defined in the JSON
     * @param rawJson raw JSOt N
     */
    explicit ResponseMessage(const QByteArray &rawJson);

    /**
     * @brief getType Retrieves type of the message
     * @return retrieved type
     */
    ResponseType getType() const;

    /**
     * @brief contains Checks whether dataKey exists as a part
     * of "data" key-value pair
     * @param dataKey a key that is expected to present under "data" object
     * @return true if dataKey is found
     */
    bool contains(const QString &dataKey) const;

    /**
     * Returns an object that is capable of parsing JSON data messages.
     *
     * Requires Response class to have the following entities:
     * * RESPONSE_OBJECT : constexpr char[] - name that defines serialized object
     * * Response::fromJson(obj : QJsonObject) : Response - a static method
     * that creates Response object
     */
    template<typename Response> Response get() const;


private:
    QJsonObject root;
};

template<typename Response> Response ResponseMessage::get() const
{
    return Response::fromJson(root["data"].toObject()
            .value(Response::RESPONSE_OBJECT).toObject());
}

#endif // RESPONSEMESSAGE_H
