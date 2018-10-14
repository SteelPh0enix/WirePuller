#include "DeviceControllerBackend.h"
#include <QDebug>
#include "DeviceName.h"

#include "RequestMessage.h"
#include "MotorSpeedRequest.h"


DeviceControllerBackend::DeviceControllerBackend(QObject *parent)
    : QObject(parent)
{
}

DeviceControllerBackend::~DeviceControllerBackend()
{

}

void DeviceControllerBackend::connectDevice(const QString &portName)
{
    port = std::unique_ptr<SerialPort>(new SerialPort(portName));
    connect(port.get(), &SerialPort::signalError,
            this, &DeviceControllerBackend::serialError);
    connect(port.get(), &SerialPort::signalError,
            this, [](QString err){ qDebug() << "Error:" << err; });
    port->open();
}

void DeviceControllerBackend::setHorizontalTranslationPwm(int pwm)
{
    RequestMessage request;
    MotorSpeedRequest motor;
    motor.setMotorSpeed(DeviceName::MotorXAxis, pwm);
    request.setData(motor);

    if (port && port->isOpen())
    {
        port->write(request.toJson());
    }
}

void DeviceControllerBackend::setWheelRotationPwm(int pwm)
{
    RequestMessage request;
    MotorSpeedRequest motor;
    motor.setMotorSpeed(DeviceName::MotorWheel, pwm);
    request.setData(motor);

    if (port && port->isOpen())
    {
        port->write(request.toJson());
    }
}

QString DeviceControllerBackend::portName() const
{
    return m_portName;
}

void DeviceControllerBackend::setPortName(QString portName)
{
    if (m_portName == portName)
        return;

    m_portName = portName;
    emit portNameChanged(m_portName);
    connectDevice(portName);
}
