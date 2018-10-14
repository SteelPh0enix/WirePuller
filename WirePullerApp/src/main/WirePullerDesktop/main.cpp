#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "WireSerialSettings.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // register types here
    qmlRegisterType<WireSerialSettings>("pl.projektorion.serial", 1, 0, "SerialSettings");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
