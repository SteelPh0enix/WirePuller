#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <QSerialPort>
#include "Messages/messageparser.hpp"
#include "Messages/wirepullerrequest.hpp"
#include "Messages/wirepullerresponse.hpp"

class Communicator {
 public:
  ~Communicator();

  void setSerialPort(QSerialPortInfo const& portInfo);
  void setSerialPort(QString const& portName);
  void setDataParser(MessageParser* parser);

  Response send(Request const& request);

  bool open();
  void close();
  void setBaudRate(QSerialPort::BaudRate baudRate);

  bool isOpen() const;

 private:
  MessageParser* messageParser{nullptr};
  QSerialPort serialPort;
};

#endif  // COMMUNICATOR_HPP
