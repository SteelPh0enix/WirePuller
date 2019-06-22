#include "axisdatamodel.h"

AxisDataModel::AxisDataModel(QObject* parent) : QObject(parent) {}

int AxisDataModel::controlValue() const {
  return m_controlValue;
}

AxisDataModel::ControlMode AxisDataModel::controlMode() const {
  return m_controlMode;
}

double AxisDataModel::distance() const {
  return m_distance;
}

bool AxisDataModel::leftEndstopState() const {
  return m_leftEndstopState;
}

bool AxisDataModel::rightEndstopState() const {
  return m_rightEndstopState;
}

double AxisDataModel::displayedSpeed() const {
  return m_displayedSpeed;
}

void AxisDataModel::setControlValue(int newValue) {
  m_controlValue = newValue;
  emit controlValueChanged(controlValue());
  emit modelChanged(this, Changed::Value);
}

void AxisDataModel::setControlMode(AxisDataModel::ControlMode newMode) {
  m_controlMode = newMode;
  emit controlModeChanged(controlMode());
  emit modelChanged(this, Changed::Mode);
}

void AxisDataModel::setDistance(double newDistance) {
  m_distance = newDistance;
  emit distanceChanged(distance());
}

void AxisDataModel::setLeftEndstopState(bool newState) {
  m_leftEndstopState = newState;
  emit leftEndstopStateChanged(leftEndstopState());
}

void AxisDataModel::setRightEndstopState(bool newState) {
  m_rightEndstopState = newState;
  emit rightEndstopStateChanged(rightEndstopState());
}

void AxisDataModel::setDisplayedSpeed(double newSpeed) {
  m_displayedSpeed = newSpeed;
  emit displayedSpeedChanged(displayedSpeed());
}
