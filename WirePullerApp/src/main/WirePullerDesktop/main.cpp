#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "WireSerialSettings.h"
#include "SerialDeviceListModel.h"
#include "DeviceControllerBackend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // register types here
    qmlRegisterType<WireSerialSettings>("pl.projektorion.serial", 1, 0, "SerialSettings");
    qmlRegisterType<SerialDeviceListModel>("pl.projektorion.serial", 1, 0, "SerialDeviceListModel");


    QQmlApplicationEngine engine;
    DeviceControllerBackend backend;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("backend", &backend);
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
