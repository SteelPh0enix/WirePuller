#include "communicator.hpp"
#include <QDebug>
#include <QThread>

Communicator::~Communicator() {
  serialPort.close();
}

QJsonDocument Communicator::send(QJsonDocument const& request,
                                 int responseTryCount,
                                 int responseWaitTime) {
  QByteArray requestBytes = request.toJson(QJsonDocument::Compact);
  qDebug() << "Sending " << requestBytes;
  requestBytes.append('\n');

  serialPort.write(requestBytes);
  QByteArray responseBytes{};
  int trialCount{0};
  while (responseBytes.isEmpty() && trialCount < responseTryCount) {
    responseBytes = serialPort.readLine();
    QThread::sleep(responseWaitTime);
  }
  qDebug() << "Received " << responseBytes;

  return QJsonDocument::fromJson(responseBytes);
}

bool Communicator::open() {
  if (serialPort.isOpen()) {
    close();
  }
  return serialPort.open(QIODevice::ReadWrite);
}

void Communicator::close() {
  serialPort.close();
}

void Communicator::setBaudRate(QSerialPort::BaudRate baudRate) {
  bool wasOpen{false};
  if (serialPort.isOpen()) {
    close();
    wasOpen = true;
  }

  serialPort.setBaudRate(baudRate);
  if (wasOpen) {
    open();
  }
}

void Communicator::setSerialPort(QSerialPortInfo const& portInfo) {
  serialPort.setPort(portInfo);
}

void Communicator::setSerialPort(QString const& portName) {
  serialPort.setPortName(portName);
}

bool Communicator::isOpen() const {
  return serialPort.isOpen();
}
