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

void AxisDataModel::setControlValue(int newValue) {
  m_controlValue = newValue;
  emit controlValueChanged(controlValue());
}

void AxisDataModel::setControlMode(AxisDataModel::ControlMode newMode) {
  m_controlMode = newMode;
  emit controlModeChanged(controlMode());
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
