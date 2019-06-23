#include "settings.h"
#include <QByteArray>
#include <QFile>

Settings::Settings(QObject* parent)
  : QObject(parent) {}

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
  settingsFile.close();

  auto settingsJson{QJsonDocument::fromJson(settingsData)};
  if (settingsJson.isEmpty()) {
    return LoadingError::InvalidContent;
  }

  updateSettings(settingsJson);

  return LoadingError::OK;
}

void Settings::updateSettings(const QJsonDocument& doc) {
  m_settingsData = doc.toVariant().toMap();
  emit settingsDataChanged();
}

QVariantMap Settings::settingsData() const {
  return m_settingsData;
}

Settings& Settings::operator=(const Settings& other) {
  m_settingsData = other.m_settingsData;
  m_settingsPath = other.m_settingsPath;
  return *this;
}
