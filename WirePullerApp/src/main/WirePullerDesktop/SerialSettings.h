#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QObject>
#include <QSerialPort>


class SerialSettings : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSerialPort::BaudRate baudrate READ baudrate WRITE setBaudrate NOTIFY baudrateChanged)
    Q_PROPERTY(QSerialPort::DataBits databits READ databits WRITE setDatabits NOTIFY databitsChanged)
    Q_PROPERTY(QSerialPort::FlowControl flowcontrol READ flowcontrol WRITE setFlowcontrol NOTIFY flowcontrolChanged)
    Q_PROPERTY(QSerialPort::Parity parity READ parity WRITE setParity NOTIFY parityChanged)
    Q_PROPERTY(QSerialPort::StopBits stopBits READ stopBits WRITE setStopBits NOTIFY stopBitsChanged)

public:
    explicit SerialSettings(const QString &organization, const QString &appName, QObject *parent = nullptr);
    explicit SerialSettings(const QString &organization, const QString &appName, bool storeOnDestroy, QObject *parent = nullptr);
    ~SerialSettings();

    QSerialPort::BaudRate baudrate() const;
    QSerialPort::DataBits databits() const;
    QSerialPort::FlowControl flowcontrol() const;
    QSerialPort::Parity parity() const;
    QSerialPort::StopBits stopBits() const;

    Q_INVOKABLE void store();


signals:
    void baudrateChanged(QSerialPort::BaudRate baudrate);
    void databitsChanged(QSerialPort::DataBits databits);
    void flowcontrolChanged(QSerialPort::FlowControl flowcontrol);
    void parityChanged(QSerialPort::Parity parity);
    void stopBitsChanged(QSerialPort::StopBits stopBits);


public slots:
    void setBaudrate(int baudrate);
    void setDatabits(int databits);
    void setFlowcontrol(int flowcontrol);
    void setParity(int parity);
    void setStopBits(int stopBits);

private:
    void _load_settings();
    void _store_settings();


    QString organization;
    QString appName;
    bool storeOnDestroy {true};

    QSerialPort::BaudRate m_baudrate {QSerialPort::Baud115200};
    QSerialPort::DataBits m_databits {QSerialPort::Data8};
    QSerialPort::FlowControl m_flowcontrol {QSerialPort::NoFlowControl};
    QSerialPort::Parity m_parity {QSerialPort::NoParity};
    QSerialPort::StopBits m_stopBits {QSerialPort::OneStop};
};

#endif // SERIALSETTINGS_H
