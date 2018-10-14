#include <QtTest>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

#include <unordered_map>

#include "RequestMessage.h"
#include "MotorSpeedRequest.h"
#include "DataRequest.h"
#include "ResetEncodersRequest.h"
#include "ResponseMessage.h"
#include "MotorResponse.h"
#include "EndstopResponse.h"
#include "EncoderResponse.h"
#include "ErrorResponse.h"


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
    bool containsValue(const QString &key, int flag) const;

    RequestMessage createNonStandard();
    QJsonObject createFeedbackData();
    ResponseMessage createResponseMessage();

    QJsonObject createErrorData();


private slots:
    void cleanup();
    void testSetType();
    void testSetNonstandardType();
    void testSetJsonObject();
    void testSetMotorSpeed();
    void testRequestData();
    void testResetEncoderRequest();
    void testParseResponseType();
    void testMotorFeedbackData();
    void testEndstopFeedbackData();
    void testEncoderFeedbackData();
    void testErrorResponse();


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

bool JsonMessageTest::containsValue(const QString &key, int flag) const
{
    return root.value(key).toInt() == flag;
}

RequestMessage JsonMessageTest::createNonStandard()
{
    RequestMessage request;
    request.setType(nonStandardType);
    return request;
}

QJsonObject JsonMessageTest::createFeedbackData()
{
    QJsonObject root;
    root["type"] = "data";
    QJsonObject motor1
    {
        {"speed", 100},
        {"current", 2000},
        {"error", false}
    };
    QJsonObject motors
    {
        {"motor1", motor1}
    };

    QJsonObject endstops
    {
        {"endstop1", false},
        {"endstop2", true}
    };

    QJsonObject encoders
    {
        {"encoder1", 20012},
        {"encoder2", -4322}
    };
    QJsonObject data
    {
        {"motors", motors},
        {"endstops", endstops},
        {"encoders", encoders}
    };
    root["data"] = data;
    return root;
}

ResponseMessage JsonMessageTest::createResponseMessage()
{
    const QJsonObject rootData {createFeedbackData()};
    const QByteArray rawJson {QJsonDocument(rootData).toJson(QJsonDocument::Compact)};

    ResponseMessage response(rawJson);
    return response;
}

QJsonObject JsonMessageTest::createErrorData()
{
    QJsonObject root;
    root["type"] = "error";
    QJsonObject errorMessage {
        {"code", 0},
        {"message", "No error"}
    };
    root["data"] = errorMessage;
    return root;
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
    MotorSpeedRequest motorSpeed;
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
    QVERIFY(containsValue("type", "set_motor_speed"));
    QVERIFY(containsValue("data", speeds));
}

void JsonMessageTest::testRequestData()
{
    RequestMessage request;
    DataRequest dataRequest;
    dataRequest.setFlag(DataFlag::MOTOR);

    request.setData(dataRequest);
    initializeJson(request.toJson());

    QVERIFY(containsKey("data"));
    QCOMPARE(root["data"].toObject()["flag"].toInt(), 1);
}

void JsonMessageTest::testResetEncoderRequest()
{
     RequestMessage request;
     ResetEncodersRequest resetEncoder;
     resetEncoder.resetEncoder("encoder1");
     QJsonObject encoders { {"encoder1", true} };

     request.setData(resetEncoder);
     initializeJson(request.toJson());
     QVERIFY(containsValue("data", encoders));
}

void JsonMessageTest::testParseResponseType()
{
    ResponseMessage response(createResponseMessage());
    QCOMPARE(response.getType(), ResponseType::DATA);
}

void JsonMessageTest::testMotorFeedbackData()
{
    ResponseMessage response(createResponseMessage());
    QVERIFY(response.contains(MotorResponse::RESPONSE_OBJECT));

    MotorResponse motors = response.get<MotorResponse>();
    QList<QString> ids = motors.getMotorIds();
    QCOMPARE(ids.size(), 1);
    QCOMPARE(ids.at(0), "motor1");
    MotorResponse::MotorData retrieved = motors.getData("motor1");
    MotorResponse::MotorData expected { false, 100, 2000 };
    QCOMPARE(retrieved, expected);

}

void JsonMessageTest::testEndstopFeedbackData()
{
    ResponseMessage response(createResponseMessage());
    QVERIFY(response.contains(EndstopResponse::RESPONSE_OBJECT));

    EndstopResponse endstops = response.get<EndstopResponse>();
    QCOMPARE(endstops.getState("endstop1"), false);
    QCOMPARE(endstops.getState("endstop2"), true);
}

void JsonMessageTest::testEncoderFeedbackData()
{
    ResponseMessage response(createResponseMessage());
    QVERIFY(response.contains(EncoderResponse::RESPONSE_OBJECT));

    EncoderResponse encoders = response.get<EncoderResponse>();
    QCOMPARE(encoders.getPosition("encoder1"), 20012);
    QCOMPARE(encoders.getPosition("encoder2"), -4322);
}

void JsonMessageTest::testErrorResponse()
{
    QJsonObject errorMsg {createErrorData()};
    ResponseMessage response(QJsonDocument(errorMsg).toJson(QJsonDocument::Compact));

    QCOMPARE(response.getType(), ResponseType::ERROR);
    ErrorResponse errorResponse = response.get<ErrorResponse>();
    QCOMPARE(errorResponse.getCode(), 0);
    QCOMPARE(errorResponse.getMessage(), "No error");
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
