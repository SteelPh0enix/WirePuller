#ifndef APPBACKEND_H
#define APPBACKEND_H

#include "axisdatamodel.h"
#include "serialcommunicator.h"
#include "settings.h"
#include <QMap>
#include <QObject>

class AppBackend : public QObject {
  Q_OBJECT
 public:
  explicit AppBackend(Settings *settings, QObject *parent = nullptr);

  AxisDataModel &xAxisData();
  AxisDataModel &wheelAxisData();
  AxisDataModel &breakerAxisData();

 signals:

 public slots:
  void setSerialPortName(QString const &name);

 private:
  Settings *m_settings{nullptr};
  QMap<QString, AxisDataModel *> m_dataModels;
  SerialCommunicator m_communicator{this};
};

#endif // APPBACKEND_H
