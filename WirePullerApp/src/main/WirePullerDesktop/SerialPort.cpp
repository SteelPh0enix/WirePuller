#include "SerialPort.h"
#include "WireSerialSettings.h"
#include <QDebug>

SerialPort::SerialPort(const QString portName, QObject *parent)
    : QObject(parent),
      uart(new QSerialPort(portName))
{
    WireSerialSettings settings(false);
    uart->setBaudRate(settings.baudrate());
    uart->setDataBits(settings.databits());
    uart->setFlowControl(settings.flowcontrol());
    uart->setParity(settings.parity());
    uart->setStopBits(settings.stopBits());

    connect(uart.data(), &QSerialPort::readyRead, this, &SerialPort::onReadyRead);
    connect(uart.data(), &QSerialPort::errorOccurred, this, &SerialPort::onError);
}

SerialPort::~SerialPort()
{

}

bool SerialPort::open()
{
    return uart->open(QIODevice::ReadWrite);
}

void SerialPort::write(const QByteArray &msg)
{
    if (uart)
    {
        uart->write(msg);
    }
}

bool SerialPort::isOpen() const
{
    return uart->isOpen();
}

void SerialPort::onReadyRead()
{
    if (uart->canReadLine())
    {
        qDebug() << uart->readLine();
    }
}

void SerialPort::onError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError)
    {
        return;
    }

    emit signalError(uart->errorString());
}
