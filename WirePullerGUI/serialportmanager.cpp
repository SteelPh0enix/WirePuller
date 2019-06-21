#include "serialportmanager.h"
#include <QSerialPortInfo>

SerialPortManager::SerialPortManager(QObject* parent) : QObject(parent) {}

void SerialPortManager::refreshPortList() {
  m_serialPortList.clear();
  auto portList = QSerialPortInfo::availablePorts();
  for (auto const& port : portList) {
    m_serialPortList.push_back(port.portName());
  }

  emit serialPortListChanged();
}

QStringList SerialPortManager::serialPortList() const {
  return m_serialPortList;
}
