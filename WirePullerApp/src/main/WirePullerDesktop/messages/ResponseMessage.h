#ifndef RESPONSEMESSAGE_H
#define RESPONSEMESSAGE_H
#include <QJsonObject>
#include <QByteArray>

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
     * @param rawJson raw JSON
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


private:
    QJsonObject root;
};

#endif // RESPONSEMESSAGE_H
