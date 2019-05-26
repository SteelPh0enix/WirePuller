#ifndef SERIALPORTINFOMANAGER_HPP
#define SERIALPORTINFOMANAGER_HPP

#include <QObject>
#include <QSerialPortInfo>
#include <QString>
#include <QVector>

class SerialPortInfoManager : public QObject {
  Q_OBJECT
 public:
  explicit SerialPortInfoManager(QObject* parent = nullptr);

  void refreshPortList();
  QVector<QString> getPortNames() const;

 private:
  QList<QSerialPortInfo> ports{};
};

#endif  // SERIALPORTINFOMANAGER_HPP
