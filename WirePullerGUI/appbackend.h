#ifndef APPBACKEND_H
#define APPBACKEND_H

#include "Requests/setmotorpowerrequest.h"
#include "axisdatamodel.h"
#include "serialcommunicator.h"
#include "settings.h"
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>
#include <QTimer>

class AppBackend : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
 public:
  explicit AppBackend(Settings* settings, QObject* parent = nullptr);

  AxisDataModel& axisData(QString const& axis);
  bool running() const;

  Q_INVOKABLE void callibrate();

 signals:
  void runningChanged(bool);

 public slots:
  void setSerialPortName(QString const& name);
  void setRunning(bool newState);

  void onModelChanged(AxisDataModel* model, AxisDataModel::Changed what);

 private:
  Settings* m_settings{nullptr};
  QMap<QString, AxisDataModel*> m_dataModels{};
  SerialCommunicator m_communicator{this};
  bool m_running{false};
  bool m_callibrating{false};

  QByteArray m_actualRequest{};
  QTimer m_timer{};

  SetMotorPowerRequest createSetMotorPowerRequest() const;
  int translatePower(
    int controlValue, int minPower, int maxPower, double minPowerSpeed, double maxPowerSpeed);

  QStringList m_axisList{"X", "Wheel", "Breaker"};
};

#endif // APPBACKEND_H
