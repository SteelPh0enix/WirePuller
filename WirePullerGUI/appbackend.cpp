#include "appbackend.h"
#include "utils.h"
#include <cmath>
#include <iostream>
#include <QThread>
#include <QtDebug>

AppBackend::AppBackend(Settings* settings, QObject* parent)
  : QObject(parent)
  , m_settings(settings)
  , m_communicator(this) {
  for (auto const& axis : m_axisList) {
    AxisDataModel* model = new AxisDataModel(this);
    model->setName(axis);
    QObject::connect(model, &AxisDataModel::modelChanged, this, &AppBackend::onModelChanged);
    m_dataModels[axis] = model;
  }

  QObject::connect(this, &AppBackend::runningChanged, [this]() {
    if (this->running()) {
      sendData();
    }
  });

  QObject::connect(&m_communicator, &SerialCommunicator::dataReceived, this,
                   &AppBackend::handleReceivedData);
  QObject::connect(this, &AppBackend::readyToSend, this, &AppBackend::sendData);
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

void AppBackend::reloadSettings() {
  m_settings->load();
}

void AppBackend::onModelChanged(AxisDataModel* model) {
  switch (model->controlMode()) {
    case AxisDataModel::ControlMode::SpeedControl: {
      auto powerAndSpeed = translateControlValue(
        model->controlValue(),
        m_settings->settingsAxisData(model->name())["minPower"].toDouble(),
        m_settings->settingsAxisData(model->name())["maxPower"].toDouble(),
        m_settings->settingsAxisData(model->name())["minPowerSpeed"].toDouble(),
        m_settings->settingsAxisData(model->name())["maxPowerSpeed"].toDouble());
      model->setControlValueUnit(QString("mm/s"));
      model->setDisplayedSpeed(powerAndSpeed.second);
      updateRequest(model->name(), powerAndSpeed.first);
      break;
    }
    case AxisDataModel::ControlMode::PowerControl: {
      int controlValue = static_cast<int>(model->controlValue());
      int controlValueSign = sign(controlValue);
      int absControlValue = std::abs(controlValue);

      int absRawPower = linearApprox(absControlValue, 0, 100, 0, 255);
      int rawPower = absRawPower * controlValueSign;

      model->setControlValueUnit(QString("%"));
      model->setDisplayedSpeed(rawPower);
      updateRequest(model->name(), rawPower);
      break;
    }
  }
}

void AppBackend::updateRequest(const QString& axis, int power) {
  m_actualRequest.setAxisPower(axis, power);
}

std::pair<int, double> AppBackend::translateControlValue(
    double controlValue,
    double minPower,
    double maxPower,
    double minPowerSpeed,
    double maxPowerSpeed) const {
  double absControlValue = std::fabs(controlValue);
  double controlValueSign = sign(controlValue);

  double absSpeed =
      linearApprox(absControlValue, 0., 100., minPowerSpeed, maxPowerSpeed);
  double absPower =
      linearApprox(absSpeed, minPowerSpeed, maxPowerSpeed, minPower, maxPower);

  return {static_cast<int>(absPower * controlValueSign),
          absSpeed * controlValueSign};
}

void AppBackend::sendData() {
  if (running()) {
    m_communicator.sendData(m_actualRequest.data());
  }
}

void AppBackend::handleReceivedData(QByteArray data) {
  QJsonParseError parsingError{};
  auto jsonResponse = QJsonDocument::fromJson(data, &parsingError);

  if (parsingError.error == QJsonParseError::NoError) {
    updateDataModelsWithResponse(jsonResponse);
  } else {
    std::cerr << "Response parsing error: "
              << parsingError.errorString().toStdString() << std::endl;
  }
  emit readyToSend();
}

void AppBackend::updateDataModelsWithResponse(QJsonDocument const& response) {
  for (auto const& axis : m_axisList) {
    auto axisResponse = response[axis].toObject();
    auto* axisModel = m_dataModels[axis];

    axisModel->setLeftEndstopState(axisResponse["EndstopLeft"].toBool());
    axisModel->setRightEndstopState(axisResponse["EndstopRight"].toBool());
    axisModel->setDistance(
      calculateDistance(axisResponse["EncoderTicks"].toDouble(),
                        m_settings->settingsData()[axis].toMap()["ticksPerMm"].toDouble(),
                        axisModel->distanceUnit()));
  }
}

double AppBackend::calculateDistance(double distance, double ticksPerMm, QString unit) const {
  // Distance: ticks
  // ticksPerMm: ticks per millimeter
  double finalDistance = distance / ticksPerMm;
  auto units = unit.split('/'); // 0 = distance, 1 = time

  if (units[0] == "cm") {
    finalDistance /= 10.;
  } else if (units[0] == "m") {
    finalDistance /= 1000.;
  }

  if (units[1] == "min") {
    finalDistance *= 60;
  } else if (units[1] == "h") {
    finalDistance *= (60 * 60);
  }

  return finalDistance;
}

void AppBackend::resetEncoders(QString axis) {
  m_running = false;
  QThread::msleep(100);
  ResetEncodersRequest request;
  request.setAxisResetState(axis, true);
  m_communicator.sendData(request.data());
  m_running = true;
}