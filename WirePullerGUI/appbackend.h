#ifndef APPBACKEND_H
#define APPBACKEND_H

#include "axisdatamodel.h"
#include "serialcommunicator.h"
#include "settings.h"
#include <QMap>
#include <QObject>

class AppBackend : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
 public:
  explicit AppBackend(Settings* settings, QObject* parent = nullptr);

  AxisDataModel& xAxisData();
  AxisDataModel& wheelAxisData();
  AxisDataModel& breakerAxisData();
  bool running() const;

  Q_INVOKABLE void callibrate();

 signals:
  void runningChanged(bool);

 public slots:
  void setSerialPortName(QString const& name);
  void setRunning(bool newState);

 private:
  Settings* m_settings{nullptr};
  QMap<QString, AxisDataModel*> m_dataModels{};
  SerialCommunicator m_communicator{this};
  bool m_running{false};
};

#endif // APPBACKEND_H
