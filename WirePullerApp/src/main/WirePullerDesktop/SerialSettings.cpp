#include "SerialSettings.h"
#include <QSettings>

namespace
{
constexpr char GROUP_SERIAL[] = "SERIAL_SETTINGS";
constexpr char KEY_BAUDRATE[] = "baudrate";
constexpr char KEY_DATABITS[] = "databits";
constexpr char KEY_FLOWCONTROL[] = "flowcontrol";
constexpr char KEY_PARITY[] = "parity";
constexpr char KEY_STOPBITS[] = "stopbits";
}

SerialSettings::SerialSettings(
        const QString &organization,
        const QString &appName,
        QObject *parent)
    : SerialSettings(organization, appName, true, parent)
{
}

SerialSettings::SerialSettings(
        const QString &organization,
        const QString &appName,
        bool storeOnDestroy,
        QObject *parent)
    : QObject(parent),
      organization{organization},
      appName{appName},
      storeOnDestroy{storeOnDestroy}
{
    _load_settings();
}

SerialSettings::~SerialSettings()
{
    if (storeOnDestroy)
    {
        _store_settings();
    }
}

QSerialPort::BaudRate SerialSettings::baudrate() const
{
    return m_baudrate;
}

QSerialPort::DataBits SerialSettings::databits() const
{
    return m_databits;
}

QSerialPort::FlowControl SerialSettings::flowcontrol() const
{
    return m_flowcontrol;
}

QSerialPort::Parity SerialSettings::parity() const
{
    return m_parity;
}

QSerialPort::StopBits SerialSettings::stopBits() const
{
    return m_stopBits;
}

void SerialSettings::store()
{
   _store_settings();
}

void SerialSettings::setBaudrate(int baudrate)
{
    auto tmp_baudrate {static_cast<QSerialPort::BaudRate>(baudrate)};
    if (m_baudrate == tmp_baudrate)
    {
        return;
    }

    m_baudrate = tmp_baudrate;
    emit baudrateChanged(m_baudrate);
}

void SerialSettings::setDatabits(int databits)
{
    auto tmp_databits {static_cast<QSerialPort::DataBits>(databits)};
    if (m_databits == tmp_databits)
    {
        return;
    }

    m_databits = tmp_databits;
    emit databitsChanged(m_databits);
}

void SerialSettings::setFlowcontrol(int flowcontrol)
{
    auto tmp_flowcontrol {static_cast<QSerialPort::FlowControl>(flowcontrol)};
    if (m_flowcontrol == tmp_flowcontrol)
    {
        return;
    }

    m_flowcontrol = tmp_flowcontrol;
    emit flowcontrolChanged(m_flowcontrol);
}

void SerialSettings::setParity(int parity)
{
    auto tmp_parity {static_cast<QSerialPort::Parity>(parity)};
    if (m_parity == tmp_parity)
    {
        return;
    }

    m_parity = tmp_parity;
    emit parityChanged(m_parity);
}

void SerialSettings::setStopBits(int stopBits)
{
    auto tmp_stopbits {static_cast<QSerialPort::StopBits>(stopBits)};
    if (m_stopBits == tmp_stopbits)
    {
        return;
    }

    m_stopBits = tmp_stopbits;
    emit stopBitsChanged(m_stopBits);
}

void SerialSettings::_load_settings()
{
    QSettings load(organization, appName);
    load.beginGroup(GROUP_SERIAL);

    setBaudrate(load.value(KEY_BAUDRATE, m_baudrate).toInt());
    setDatabits(load.value(KEY_DATABITS, m_databits).toInt());
    setFlowcontrol(load.value(KEY_FLOWCONTROL, m_flowcontrol).toInt());
    setParity(load.value(KEY_PARITY, m_parity).toInt());
    setStopBits(load.value(KEY_STOPBITS, m_stopBits).toInt());
}

void SerialSettings::_store_settings()
{
    QSettings save(organization, appName);
    save.beginGroup(GROUP_SERIAL);

    save.setValue(KEY_BAUDRATE, baudrate());
    save.setValue(KEY_DATABITS, databits());
    save.setValue(KEY_FLOWCONTROL, flowcontrol());
    save.setValue(KEY_PARITY, parity());
    save.setValue(KEY_STOPBITS, stopBits());
}
