#ifndef APPBACKEND_H
#define APPBACKEND_H

#include "Requests/resetencodersrequest.h"
#include "Requests/setmotorpowerrequest.h"
#include "axisdatamodel.h"
#include "serialcommunicator.h"
#include "settings.h"
#include <utility>
#include <QMap>
#include <QObject>
#include <QString>
#include <QStringList>

class AppBackend : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
 public:
  explicit AppBackend(Settings* settings, QObject* parent = nullptr);

  AxisDataModel& axisData(QString const& axis);
  bool running() const;

  Q_INVOKABLE void reloadSettings();
  Q_INVOKABLE void resetEncoders(QString axis);

 signals:
  void runningChanged(bool);
  void readyToSend();

 public slots:
  void setSerialPortName(QString const& name);
  void setRunning(bool newState);

  void onModelChanged(AxisDataModel* model);

  void sendData();
  void handleReceivedData(QByteArray data);

 private:
  Settings* m_settings{nullptr};
  QMap<QString, AxisDataModel*> m_dataModels{};
  SerialCommunicator m_communicator{this};
  bool m_running{false};
  bool m_callibrating{false};

  SetMotorPowerRequest m_actualRequest{};

  void updateRequest(QString const& axis, int power);
  std::pair<int, double> translateControlValue(double controlValue,
                                               double minPower,
                                               double maxPower,
                                               double minPowerSpeed,
                                               double maxPowerSpeed) const;

  QStringList m_axisList{"X", "Wheel", "Breaker"};

  void updateDataModelsWithResponse(QJsonDocument const& response);
  double calculateDistance(double distance, double ticksPerMm, QString unit) const;
};

#endif  // APPBACKEND_H
