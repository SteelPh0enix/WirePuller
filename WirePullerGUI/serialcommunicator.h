#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QString>

class SerialCommunicator : public QObject
{
    Q_OBJECT
public:
    explicit SerialCommunicator(QObject *parent = nullptr);

signals:
    void dataReceived(QByteArray data);

public slots:
    void sendData(QByteArray data);
    void setSerialPort(QString name);

private slots:
    void internalReceiveData();

private:
    QSerialPort serialPort;
};

#endif // SERIALCOMMUNICATOR_H
