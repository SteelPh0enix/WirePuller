#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QStringList>

class SerialPortManager : public QObject {
  Q_OBJECT
  Q_PROPERTY(QStringList serialPortList READ serialPortList NOTIFY serialPortListChanged)
 public:
  explicit SerialPortManager(QObject *parent = nullptr);
  virtual ~SerialPortManager() = default;

  QStringList serialPortList() const;

 public slots:
  void refreshPortList();

 signals:
  void serialPortListChanged();

 private:
  QStringList m_serialPortList;
};

#endif // SERIALPORTMANAGER_H
