#ifndef WIREPULLER_HPP
#define WIREPULLER_HPP

#include <QMap>
#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QTimer>
#include "communicator.hpp"
#include "uidata.hpp"

class WirePuller : public QObject {
  Q_OBJECT
  constexpr static unsigned TICK_HISTERESIS{10};

 public:
  WirePuller(QObject* parent = nullptr);

  bool setSerialPort(QString const& portName);

  bool movingState() const;
  bool isPortOpen() const;

 signals:
  void serialPortOpened(bool flag);
  void movingStateFeedback(bool state);
  void updateData(UIData::Axis axis, UIData::AxisInputData const& data);

 public slots:
  void openSerialPort(QString const& portName);
  void startMoving();
  void stopMoving();
  void callibrate();

  void axisPowerUpdated(UIData::Axis axis, int power);
  void axisPositionUpdate(UIData::Axis axis, double position);
  void axisModeUpdated(UIData::Axis axis, UIData::AxisOutputData::Mode mode);

 private slots:
  void sendData();

 private:
  void setMovingState(bool state);
  bool movingStateFlag{false};

  Communicator communicator{};

  QTimer communicatorTimer{};

  QMap<UIData::Axis, UIData::AxisOutputData> storedData{};

  QJsonObject storedDataToJson() const;
  QMap<UIData::Axis, UIData::AxisInputData> responseToInputData(
      QJsonDocument const& response) const;

  void checkDistances(QMap<UIData::Axis, UIData::AxisInputData>& data);
};

#endif  // WIREPULLER_HPP
