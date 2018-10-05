#include <QtTest>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>


class JsonMessageTest : public QObject
{
    Q_OBJECT

    QJsonDocument document;
    QJsonObject root;

public:
    JsonMessageTest();
    ~JsonMessageTest();

    void initializeJson(const QByteArray &json);
    bool containsKey(const QString &key) const;

private slots:
    void cleanup();
    void test_set_motor_speed_request();

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
}

bool JsonMessageTest::containsKey(const QString &key) const
{
    return root.contains(key);
}

void JsonMessageTest::cleanup()
{
    document = QJsonDocument();
    root = QJsonObject();
}

void JsonMessageTest::test_set_motor_speed_request()
{
    RequestMessage request;
    request.setType(RequestMessage::MOTOR_SPEED);

    QByteArray rawJson = request.toJson();
    initializeJson(rawJson);
    QVERIFY(containsKey("type"));
}

QTEST_APPLESS_MAIN(JsonMessageTest)

#include "tst_jsonmessagetest.moc"
