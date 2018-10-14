#ifndef DEVICECONTROLLERBACKEND_H
#define DEVICECONTROLLERBACKEND_H

#include <QObject>
#include <memory>

#include "SerialPort.h"
#include "MotorResponse.h"


class DeviceControllerBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString portName READ portName WRITE setPortName NOTIFY portNameChanged)

public:
    explicit DeviceControllerBackend(QObject *parent = nullptr);
    ~DeviceControllerBackend();

    /**
     * @brief connect Connect a serial device
     * @param portName port name of the device
     */
    void connectDevice(const QString &portName);


    /**
     * @brief setHorizontalTranslationPwm
     * @param pwm
     */
    Q_INVOKABLE void setHorizontalTranslationPwm(int pwm);

    /**
     * @brief setWheelRotationPwm
     * @param pwm
     */
    Q_INVOKABLE void setWheelRotationPwm(int pwm);

    QString portName() const;


signals:
    void portNameChanged(QString portName);
    void serialError(QString error);
    void hello(QString error);


public slots:
    void setPortName(QString portName);


private:
    std::unique_ptr<SerialPort> port;

    QString m_portName;
};

#endif // DEVICECONTROLLERBACKEND_H
