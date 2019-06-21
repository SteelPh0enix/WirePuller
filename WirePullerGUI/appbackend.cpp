#include "appbackend.h"
#include <QtDebug>

AppBackend::AppBackend(Settings* settings, QObject *parent) : QObject(parent), m_settings(settings), m_communicator(this) {
    m_dataModels.insert("X", new AxisDataModel(this));
    m_dataModels.insert("Wheel", new AxisDataModel(this));
    m_dataModels.insert("Breaker", new AxisDataModel(this));
}

void AppBackend::setSerialPortName(QString const& portName) {
    m_communicator.setSerialPort(portName);
    qDebug() << "Serial port name set to" << m_communicator.serialPortName();
}

AxisDataModel& AppBackend::xAxisData() {
    return *m_dataModels["X"];
}

AxisDataModel& AppBackend::wheelAxisData() {
    return *m_dataModels["Wheel"];
}

AxisDataModel& AppBackend::breakerAxisData() {
    return *m_dataModels["Breaker"];
}
