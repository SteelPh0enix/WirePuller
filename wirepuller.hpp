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
 public:
  WirePuller(QObject* parent = nullptr);

  bool setSerialPort(QString const& portName);

  bool movingState() const;
  bool isPortOpen() const;

 signals:
  void serialPortOpened(bool flag);
  void movingStateFeedback(bool state);
  void updateUI(UIData::Axis axis, UIData::AxisInputData const& data);

 public slots:
  void openSerialPort(QString const& portName);
  void startMoving();
  void stopMoving();
  void callibrate();
  void axisUpdated(UIData::Axis axis, UIData::AxisOutputData const& data);

 private slots:
  void sendData() const;

 private:
  void setMovingState(bool state);
  bool movingStateFlag{false};

  Communicator communicator;

  QTimer communicatorTimer;

  QMap<UIData::Axis, UIData::AxisOutputData> storedData;
};

#endif  // WIREPULLER_HPP
