#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QByteArray>
#include <QObject>
#include <QSerialPort>
#include <QString>

class SerialCommunicator : public QObject {
  Q_OBJECT
 public:
  explicit SerialCommunicator(QObject* parent = nullptr);

  QString serialPortName() const;
  bool isOpen() const;

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
