#include "appbackend.h"
#include "utils.h"
#include <cmath>
#include <QtDebug>

AppBackend::AppBackend(Settings* settings, QObject* parent)
  : QObject(parent)
  , m_settings(settings)
  , m_communicator(this) {
  m_timer.setInterval(100);

  for (auto const& axis : m_axisList) {
    AxisDataModel* model = new AxisDataModel(this);
    QObject::connect(model, &AxisDataModel::modelChanged, this, &AppBackend::onModelChanged);
    m_dataModels[axis] = model;
  }
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

void AppBackend::onModelChanged(AxisDataModel* model, AxisDataModel::Changed what) {}

SetMotorPowerRequest AppBackend::createSetMotorPowerRequest() const {
  SetMotorPowerRequest request{};

  for (auto axis : m_axisList) {
  }

  return request;
}

int AppBackend::translatePower(
  int controlValue, int minPower, int maxPower, double minPowerSpeed, double maxPowerSpeed) {}
