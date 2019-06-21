#include "appbackend.h"
#include "serialportmanager.h"
#include "settings.h"
#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  qmlRegisterType<SerialPortManager>("steelph0enix.serialportmanager", 1, 0, "SerialPortManager");
  qmlRegisterType<Settings>("steelph0enix.settings", 1, 0, "ProgramSettings");
  qmlRegisterType<AxisDataModel>("steelph0enix.axisdatamodel", 1, 0, "AxisDataModel");

  Settings programSettings;
  programSettings.setPath("./settings.json");
  auto loadFlag = programSettings.load();
  if (loadFlag != Settings::OK) {
    std::cerr << "Unable to load settings!\n";
    return 1;
  }

  AppBackend backend{&programSettings};

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine,
                   &QQmlApplicationEngine::objectCreated,
                   &app,
                   [url](QObject *obj, const QUrl &objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);

  engine.rootContext()->setContextProperty("programSettings", &programSettings);
  engine.rootContext()->setContextProperty("backend", &backend);
  engine.rootContext()->setContextProperty("xAxisData", &backend.xAxisData());
  engine.rootContext()->setContextProperty("wheelAxisData", &backend.wheelAxisData());
  engine.rootContext()->setContextProperty("breakerAxisData", &backend.breakerAxisData());

  engine.load(url);

  return app.exec();
}
