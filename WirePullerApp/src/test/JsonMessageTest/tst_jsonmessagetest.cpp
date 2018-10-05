#include <QtTest>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <unordered_map>
#include "messages/RequestMessage.h"
class JsonMessageTest : public QObject
{
    Q_OBJECT

    const QString nonStandardType {"non-standard-type"};

    QJsonDocument document;
    QJsonObject root;

public:
    JsonMessageTest();
    ~JsonMessageTest();

    void initializeJson(const QByteArray &json);
    bool containsKey(const QString &key) const;
    bool containsValue(const QString &key, const QString &value) const;
    bool containsValue(const QString &key, const QJsonObject &value) const;

    RequestMessage createNonStandard();

private slots:
    void cleanup();
    void testSetType();
    void testSetNonstandardType();
    void testSetJsonObject();
    void testSetMotorSpeed();


private:
    void verifyRequestTypes(const std::unordered_map<RequestType, QString> &typeMapping);

};

JsonMessageTest::JsonMessageTest()
{

}

JsonMessageTest::~JsonMessageTest()
{

}

void JsonMessageTest::initializeJson(const QByteArray &json)
{
    QJsonParseError error;
    document = QJsonDocument::fromJson(json, &error);
    if (error.error != QJsonParseError::NoError)
    {
        QFAIL("Experienced an error when parsing JSON.");
    }
    root = document.object();
}

bool JsonMessageTest::containsKey(const QString &key) const
{
    return root.contains(key);
}

bool JsonMessageTest::containsValue(const QString &key, const QString &value) const
{
    return root.value(key).toString() == value;
}

bool JsonMessageTest::containsValue(const QString &key, const QJsonObject &value) const
{
    return root.value(key).toObject() == value;
}

RequestMessage JsonMessageTest::createNonStandard()
{
    RequestMessage request;
    request.setType(nonStandardType);
    return request;
}

void JsonMessageTest::cleanup()
{
    document = QJsonDocument();
    root = QJsonObject();
}

void JsonMessageTest::testSetType()
{
    verifyRequestTypes({
        {RequestType::SET_MOTOR_SPEED, "set_motor_speed"},
        {RequestType::GET_DATA, "data_request"},
        {RequestType::RESET_ENCODER, "reset_encoder"}});
}

void JsonMessageTest::testSetNonstandardType()
{
    RequestMessage request {createNonStandard()};
    QByteArray rawJson = request.toJson();
    initializeJson(rawJson);
    QVERIFY(containsKey("type"));
    QVERIFY(containsValue("type", nonStandardType));
}

void JsonMessageTest::testSetJsonObject()
{
    auto request {createNonStandard()};
    QJsonObject data
    {
        {"entry1", "value1"},
        {"entry2", "value2"}
    };

    request.setData(QJsonObject(data));
    auto rawJson {request.toJson()};
    initializeJson(rawJson);

    QVERIFY(containsValue("data", data));
}

void JsonMessageTest::testSetMotorSpeed()
{
    RequestMessage request;
    request.setType(RequestType::SET_MOTOR_SPEED);
    MotorSpeedMessage motorSpeed;
    QJsonObject speeds {
        {"motor1", 100},
        {"motor2", -500},
        {"motor3", 666},
        {"motor4", -256},
    };
    for (auto it=std::begin(speeds); it != std::end(speeds); ++it)
    {
        motorSpeed.setMotorSpeed(it.key(), it.value().toInt());
    }

    request.setData(motorSpeed);
    initializeJson(request.toJson());

    // the value must be correctly recognized and corrected
    speeds["motor2"] = -400;
    speeds["motor3"] = 400;
    QVERIFY(containsValue("data", speeds));
}

void JsonMessageTest::verifyRequestTypes(const std::unordered_map<RequestType, QString> &typeMapping)
{
    for (const auto &record : typeMapping)
    {
        RequestMessage request;
        request.setType(record.first);

        QByteArray rawJson = request.toJson();
        initializeJson(rawJson);
        QVERIFY(containsKey("type"));
        QVERIFY(containsValue("type", record.second));
    }
}

QTEST_APPLESS_MAIN(JsonMessageTest)

#include "tst_jsonmessagetest.moc"
