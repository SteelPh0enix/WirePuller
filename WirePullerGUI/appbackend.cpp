#include "appbackend.h"
#include "utils.h"
#include <cmath>
#include <iostream>
#include <QThread>
#include <QtDebug>

namespace {
void updateModelWithSettingsData(QString axis, AxisDataModel& model, Settings const& settings) {
  model.setTicksPerMm(settings.axisData(axis)["ticksPerMm"].toDouble());
  model.setMinPWM(settings.axisData(axis)["minPower"].toDouble());
  model.setMaxPWM(settings.axisData(axis)["maxPower"].toDouble());
  model.setMinSpeed(settings.axisData(axis)["minPowerSpeed"].toDouble());
  model.setMaxSpeed(settings.axisData(axis)["maxPowerSpeed"].toDouble());
}
} // namespace

AppBackend::AppBackend(Settings* settings, QObject* parent)
  : QObject(parent)
  , m_settings(settings)
  , m_communicator(this) {
  for (auto const& axis : m_axisList) {
    AxisDataModel* model = new AxisDataModel(this);
    model->setName(axis);
    updateModelWithSettingsData(axis, *model, *m_settings);

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
  for (auto it = m_dataModels.begin(); it != m_dataModels.end(); it++) {
    updateModelWithSettingsData(it.key(), *(it.value()), *m_settings);
  }
}

void AppBackend::onModelChanged(AxisDataModel* model) {
  updateRequest(model->name(), static_cast<int>(model->power()));
}

void AppBackend::updateRequest(const QString& axis, int power) {
  m_actualRequest.setAxisPower(axis, power);
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
    axisModel->setEncoderValue(axisResponse["EncoderTicks"].toDouble());
  }
}

void AppBackend::resetEncoders(QString axis) {
  if (!m_communicator.isOpen()) {
    return;
  }

  m_running = false;
  QThread::msleep(100);
  ResetEncodersRequest request;
  request.setAxisResetState(axis, true);
  m_communicator.sendData(request.data());
  m_running = true;
}
