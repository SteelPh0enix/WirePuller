#ifndef MESSAGE_H
#define MESSAGE_H
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

#endif // MESSAGE_H
