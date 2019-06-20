#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "serialportmanager.h"
#include "settings.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<SerialPortManager>("steelph0enix.serialportmanager", 1, 0, "SerialPortManager");
    qmlRegisterType<Settings>("steelph0enix.settings", 1, 0, "ProgramSettings");

    Settings programSettings;
    programSettings.setPath("./settings.json");
    auto loadFlag = programSettings.load();
    if (loadFlag != Settings::OK) {
        std::cerr << "Unable to load settings!\n";
        return 1;
    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);


    engine.rootContext()->setContextProperty("programSettings", &programSettings);
    engine.load(url);

    return app.exec();
}
