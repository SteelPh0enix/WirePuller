#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <QJsonDocument>
#include <QSerialPort>

class Communicator {
 public:
  ~Communicator();

  void setSerialPort(QSerialPortInfo const& portInfo);
  void setSerialPort(QString const& portName);

  QJsonDocument send(QJsonDocument const& request,
                     int responseTryCount = 10,
                     int responseWaitTime = 100);

  bool open();
  void close();
  void setBaudRate(QSerialPort::BaudRate baudRate);

  bool isOpen() const;

 private:
  QSerialPort serialPort;
};

#endif  // COMMUNICATOR_HPP
