#include <QtTest>

// add necessary includes here

class JsonMessageTest : public QObject
{
    Q_OBJECT

public:
    JsonMessageTest();
    ~JsonMessageTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

JsonMessageTest::JsonMessageTest()
{

}

JsonMessageTest::~JsonMessageTest()
{

}

void JsonMessageTest::initTestCase()
{

}

void JsonMessageTest::cleanupTestCase()
{

}

void JsonMessageTest::test_case1()
{

}

QTEST_APPLESS_MAIN(JsonMessageTest)

#include "tst_jsonmessagetest.moc"
