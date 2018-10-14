#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QScopedPointer>


class SerialPort : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SerialPort)

public:
    explicit SerialPort(const QString portName, QObject *parent = nullptr);
    ~SerialPort();

    bool open();
    void write(const QByteArray &msg);

    bool isOpen() const;


signals:
    void signalError(const QString &errorString);


private slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError error);


private:
    QScopedPointer<QSerialPort> uart;
};

#endif // SERIALPORT_H
