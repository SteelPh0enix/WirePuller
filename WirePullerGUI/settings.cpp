#include "settings.h"
#include <QByteArray>
#include <QFile>

Settings::Settings(QObject *parent) : QObject(parent) {}

AxisData Settings::xAxisData() const {
    return m_xAxisData;
}

AxisData Settings::wheelAxisData() const {
    return m_wheelAxisData;
}

AxisData Settings::breakerAxisData() const {
    return m_breakerAxisData;
}

void Settings::setPath(QString const& path) {
    m_settingsPath = path;
}

Settings::LoadingError Settings::load() {
    if (m_settingsPath.isEmpty()) {
        return LoadingError::InvalidPath;
    }

    QFile settingsFile(m_settingsPath);
    if (!settingsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return LoadingError::UnableToOpen;
    }

    QByteArray settingsData{settingsFile.readAll()};
    if (settingsData.isEmpty()) {
        return LoadingError::EmptyFile;
    }

    auto settingsJson{QJsonDocument::fromJson(settingsData)};
    if (settingsJson.isEmpty()) {
        return LoadingError::InvalidContent;
    }

    updateSettings(settingsJson);

    return LoadingError::None;
}

void Settings::updateSettings(const QJsonDocument &doc) {
    updateAxisSettings(m_xAxisData, doc["X"].toObject());
    emit xAxisDataChanged();
    updateAxisSettings(m_wheelAxisData, doc["Wheel"].toObject());
    emit wheelAxisDataChanged();
    updateAxisSettings(m_breakerAxisData, doc["Breaker"].toObject());
    emit breakerAxisDataChanged();
}

void Settings::updateAxisSettings(AxisData &axis, const QJsonObject &settings) {
    axis.ticksPerMillimeter = settings["TicksPerMm"].toInt();
    axis.ticksPerPower.minPowerLevel = settings["TicksPerPower"]["MinPowerLevel"].toInt();
    axis.ticksPerPower.maxPowerLevel = settings["TicksPerPower"]["MaxPowerLevel"].toInt();
    axis.ticksPerPower.minPowerTicks = settings["TicksPerPower"]["MinPowerTicks"].toInt();
    axis.ticksPerPower.maxPowerTicks = settings["TicksPerPower"]["MaxPowerTicks"].toInt();
}
