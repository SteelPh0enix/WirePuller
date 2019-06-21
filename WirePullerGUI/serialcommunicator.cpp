#include "serialcommunicator.h"
#include <QThread>

SerialCommunicator::SerialCommunicator(QObject *parent) : QObject(parent) {
    serialPort.setBaudRate(QSerialPort::Baud115200);

    QObject::connect(&serialPort, &QSerialPort::readyRead, this, &SerialCommunicator::internalReceiveData);
}

void SerialCommunicator::sendData(QByteArray data) {
    serialPort.write(data);
}

void SerialCommunicator::setSerialPort(QString portName) {
    serialPort.setPortName(portName);
    serialPort.open(QIODevice::ReadWrite);
    QThread::sleep(1); // Wait for Arduino startup
}

void SerialCommunicator::internalReceiveData() {
    emit dataReceived(serialPort.readAll());
}

QString SerialCommunicator::serialPortName() const {
    return serialPort.portName();
}
