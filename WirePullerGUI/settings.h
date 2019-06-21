#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(LoadingError)
    Q_PROPERTY(QVariantMap settingsData READ settingsData NOTIFY settingsDataChanged)
public:
    explicit Settings(QObject *parent = nullptr);
    Settings& operator=(Settings const& other);

    enum LoadingError {
        OK = 0,
        InvalidPath,
        UnableToOpen,
        EmptyFile,
        InvalidContent
    };

    QVariantMap settingsData() const;

public slots:
    void setPath(QString const& path);
    LoadingError load();

signals:
    void settingsDataChanged();

private:
    QVariantMap m_settingsData{};
    QString m_settingsPath{};

    void updateSettings(QJsonDocument const& doc);
    QVariantMap getAxisSettings(QJsonObject const& settings);
};

Q_DECLARE_METATYPE(Settings::LoadingError)

#endif // SETTINGS_H
