#include "appbackend.h"
#include <QtDebug>

AppBackend::AppBackend(Settings* settings, QObject* parent)
  : QObject(parent)
  , m_settings(settings)
  , m_communicator(this) {
  m_dataModels.insert("X", new AxisDataModel(this));
  m_dataModels.insert("Wheel", new AxisDataModel(this));
  m_dataModels.insert("Breaker", new AxisDataModel(this));
}

void AppBackend::setSerialPortName(QString const& portName) {
  m_communicator.setSerialPort(portName);
}

AxisDataModel& AppBackend::axisData(QString const& key) {
  return *m_dataModels[key];
}

bool AppBackend::running() const {
  return m_running;
}

void AppBackend::setRunning(bool newState) {
  if (newState) {
    if (m_communicator.isOpen()) {
      m_running = true;
      emit runningChanged(running());
    }
  } else {
    m_running = false;
    emit runningChanged(running());
  }
}

void AppBackend::callibrate() {}
