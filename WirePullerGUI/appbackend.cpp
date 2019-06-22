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
    model->setName(axis);
    QObject::connect(model, &AxisDataModel::modelChanged, this, &AppBackend::onModelChanged);
    m_dataModels[axis] = model;
  }

  QObject::connect(&m_timer, &QTimer::timeout, this, &AppBackend::sendData);
  QObject::connect(this, &AppBackend::runningChanged, [this]() {
    if (this->running()) {
      m_timer.start();
    } else {
      m_timer.stop();
    }
  });

  QObject::connect(&m_communicator,
                   &SerialCommunicator::dataReceived,
                   this,
                   &AppBackend::handleReceivedData);
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

void AppBackend::onModelChanged(AxisDataModel* model) {
  auto powerAndSpeed = translateControlValue(
    model->controlValue(),
    m_settings->settingsData()[model->name()].toMap()["minPower"].toDouble(),
    m_settings->settingsData()[model->name()].toMap()["maxPower"].toDouble(),
    m_settings->settingsData()[model->name()].toMap()["minPowerSpeed"].toDouble(),
    m_settings->settingsData()[model->name()].toMap()["maxPowerSpeed"].toDouble());

  model->setDisplayedSpeed(powerAndSpeed.second);
  updateRequest(model->name(), powerAndSpeed.first);
}

void AppBackend::updateRequest(const QString& axis, int power) {
  m_actualRequest.setAxisPower(axis, power);
}

std::pair<int, double> AppBackend::translateControlValue(double controlValue,
                                                         double minPower,
                                                         double maxPower,
                                                         double minPowerSpeed,
                                                         double maxPowerSpeed) const {
  double absControlValue = std::fabs(controlValue);
  double controlValueSign = sign(controlValue);

  double absSpeed = linearApprox(absControlValue, 0., 100., minPowerSpeed, maxPowerSpeed);
  double absPower = linearApprox(absSpeed, minPowerSpeed, maxPowerSpeed, minPower, maxPower);

  return {static_cast<int>(absPower * controlValueSign), absSpeed * controlValueSign};
}

void AppBackend::sendData() {
  m_communicator.sendData(m_actualRequest.data());
}

void AppBackend::handleReceivedData(QByteArray data) {
  qDebug() << "Received:" << data;
  // TODO: Converting byte data to structure and refreshing UI state
}
