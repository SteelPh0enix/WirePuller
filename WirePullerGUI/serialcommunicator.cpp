#include "serialcommunicator.h"
#include <QThread>
#include <QtDebug>
#include <iostream>

SerialCommunicator::SerialCommunicator(QObject* parent) : QObject(parent) {
    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setReadBufferSize(256);

    QObject::connect(&serialPort, &QSerialPort::readyRead, this,
                     &SerialCommunicator::internalReceiveData);
}

void SerialCommunicator::sendData(QByteArray data) {
    data.append('\n');
    serialPort.write(data);
}

void SerialCommunicator::setSerialPort(QString portName) {
    serialPort.setPortName(portName);
    bool openingSuccesful = serialPort.open(QIODevice::ReadWrite);
    if (!openingSuccesful) {
        std::cerr << "Unable to open serial port.\nOn Windows: check if Arduino is properly recognized in device manager, and if drivers are working.\nOn Linux: install udev rule allowing user to access serial port, or run application as root (NOT RECOMMENDED!)" << std::endl;
    } else {
        QThread::sleep(1);  // Wait for Arduino startup
    }
}

void SerialCommunicator::internalReceiveData() {
    auto received = serialPort.readLine();
    internalBuffer += received;
    if (internalBuffer.length() > 10 && internalBuffer.endsWith('\n')) {
        emit dataReceived(internalBuffer);
        internalBuffer.clear();
    }
}

QString SerialCommunicator::serialPortName() const {
    return serialPort.portName();
}

bool SerialCommunicator::isOpen() const {
    return serialPort.isOpen();
}
