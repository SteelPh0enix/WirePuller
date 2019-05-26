#include "serialportinfomanager.hpp"
#include <QSerialPortInfo>
#include <algorithm>

SerialPortInfoManager::SerialPortInfoManager(QObject* parent)
    : QObject(parent) {}

void SerialPortInfoManager::refreshPortList() {
  ports = QSerialPortInfo::availablePorts();
}

QVector<QString> SerialPortInfoManager::getPortNames() const {
  QVector<QString> portNames(ports.size());
  std::transform(ports.begin(), ports.end(), portNames.begin(),
                 [](QSerialPortInfo const& port) { return port.portName(); });
  return portNames;
}
