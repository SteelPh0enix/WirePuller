#include "axisdatamodel.h"

AxisDataModel::AxisDataModel(QObject* parent)
  : QObject(parent) {}

double AxisDataModel::power() const {
  return m_power;
}

double AxisDataModel::encoderValue() const {
  return m_encoderValue;
}

bool AxisDataModel::leftEndstopState() const {
  return m_leftEndstopState;
}

bool AxisDataModel::rightEndstopState() const {
  return m_rightEndstopState;
}

QString AxisDataModel::name() const {
  return m_name;
}

double AxisDataModel::ticksPerMm() const {
  return m_ticksPerMm;
}

double AxisDataModel::minPWM() const {
  return m_minPWM;
}

double AxisDataModel::maxPWM() const {
  return m_maxPWM;
}

double AxisDataModel::minSpeed() const {
  return m_minSpeed;
}

double AxisDataModel::maxSpeed() const {
  return m_maxSpeed;
}

void AxisDataModel::setPower(double newValue) {
  m_power = newValue;
  emit powerChanged(power());
  emit modelChanged(this);
}

void AxisDataModel::setEncoderValue(double newDistance) {
  m_encoderValue = newDistance;
  emit encoderValueChanged(encoderValue());
}

void AxisDataModel::setLeftEndstopState(bool newState) {
  m_leftEndstopState = newState;
  emit leftEndstopStateChanged(leftEndstopState());
}

void AxisDataModel::setRightEndstopState(bool newState) {
  m_rightEndstopState = newState;
  emit rightEndstopStateChanged(rightEndstopState());
}

void AxisDataModel::setName(QString const& newName) {
  m_name = newName;
}

void AxisDataModel::setTicksPerMm(double ticks) {
  m_ticksPerMm = ticks;
  emit ticksPerMmChanged(ticksPerMm());
}

void AxisDataModel::setMinPWM(double pwm) {
  m_minPWM = pwm;
  emit minPWMChanged(minPWM());
}

void AxisDataModel::setMaxPWM(double pwm) {
  m_maxPWM = pwm;
  emit maxPWMChanged(maxPWM());
}

void AxisDataModel::setMinSpeed(double speed) {
  m_minSpeed = speed;
  emit minSpeedChanged(minSpeed());
}

void AxisDataModel::setMaxSpeed(double speed) {
  m_maxSpeed = speed;
  emit maxSpeedChanged(maxSpeed());
}
