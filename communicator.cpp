#include "communicator.hpp"

Communicator::~Communicator() {
  serialPort.close();
}

Response Communicator::send(Request const& request) {
  if (messageParser == nullptr) {
    return Response{};
  }

  QByteArray rawRequest = messageParser->parseRequest(request);
  serialPort.write(rawRequest);

  QByteArray rawResponse = serialPort.readLine();

  return messageParser->parseResponse(rawResponse);
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

void Communicator::setDataParser(MessageParser* parser) {
  messageParser = parser;
}

bool Communicator::isOpen() const {
  return serialPort.isOpen();
}
