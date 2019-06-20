#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

class TicksPerPower : public QObject {
    Q_OBJECT
    Q_PROPERTY(int minPowerLevel READ minPowerLevel WRITE setMinPowerLevel NOTIFY minPowerLevelChanged)
    Q_PROPERTY(int maxPowerLevel READ maxPowerLevel WRITE setMaxPowerLevel NOTIFY maxPowerLevelChanged)
    Q_PROPERTY(int minPowerTicks READ minPowerTicks WRITE setMinPowerTicks NOTIFY minPowerTicksChanged)
    Q_PROPERTY(int maxPowerTicks READ maxPowerTicks WRITE setMaxPowerTicks NOTIFY maxPowerTicksChanged)

public:
    explicit TicksPerPower(QObject* parent = nullptr) : QObject(parent) {}
    TicksPerPower(TicksPerPower const& other) {
        m_minPowerLevel = other.m_minPowerLevel;
        m_maxPowerLevel = other.m_maxPowerLevel;
        m_minPowerTicks = other.m_minPowerTicks;
        m_maxPowerTicks = other.m_maxPowerTicks;
    }

    int minPowerLevel() const { return m_minPowerLevel; }
    int maxPowerLevel() const { return m_maxPowerLevel; }
    int minPowerTicks() const { return m_minPowerTicks; }
    int maxPowerTicks() const { return m_maxPowerTicks; }

    void setMinPowerLevel(int level) { m_minPowerLevel = level; emit minPowerLevelChanged(); }
    void setMaxPowerLevel(int level) { m_maxPowerLevel = level; emit maxPowerLevelChanged(); }
    void setMinPowerTicks(int ticks) { m_minPowerTicks = ticks; emit minPowerTicksChanged(); }
    void setMaxPowerTicks(int ticks) { m_maxPowerTicks = ticks; emit maxPowerTicksChanged(); }

signals:
    void minPowerLevelChanged();
    void maxPowerLevelChanged();
    void minPowerTicksChanged();
    void maxPowerTicksChanged();

private:
    int m_minPowerLevel{};
    int m_minPowerTicks{};

    int m_maxPowerLevel{};
    int m_maxPowerTicks{};
};

struct AxisData : public QObject {
    Q_OBJECT
    Q_PROPERTY(int ticksPerMillimeter READ ticksPerMillimeter WRITE setTicksPerMillimeter NOTIFY ticksPerMillimeterChanged)
    Q_PROPERTY(TicksPerPower ticksPerPower READ ticksPerPower WRITE setTicksPerPower NOTIFY ticksPerPowerChanged)

public:
    explicit AxisData(QObject* parent = nullptr) : QObject(parent) {}

    int ticksPerMillimeter() const { return m_ticksPerMillimeter; }
    TicksPerPower ticksPerPower() const { return m_ticksPerPower; }

private:
    int m_ticksPerMillimeter{};
    TicksPerPower m_ticksPerPower{};
};

class Settings : public QObject
{
    Q_OBJECT
    Q_ENUMS(LoadingError)
    Q_PROPERTY(AxisData xAxisData READ xAxisData NOTIFY xAxisDataChanged)
    Q_PROPERTY(AxisData wheelAxisData READ wheelAxisData NOTIFY wheelAxisDataChanged)
    Q_PROPERTY(AxisData breakerAxisData READ breakerAxisData NOTIFY breakerAxisDataChanged)
public:
    explicit Settings(QObject *parent = nullptr);

    AxisData xAxisData() const;
    AxisData wheelAxisData() const;
    AxisData breakerAxisData() const;

    enum class LoadingError {
        None,
        InvalidPath,
        UnableToOpen,
        EmptyFile,
        InvalidContent
    };

public slots:
    void setPath(QString const& path);
    LoadingError load();

signals:
    void xAxisDataChanged();
    void wheelAxisDataChanged();
    void breakerAxisDataChanged();

private:
    AxisData m_xAxisData{};
    AxisData m_wheelAxisData{};
    AxisData m_breakerAxisData{};
    QString m_settingsPath{};

    void updateSettings(QJsonDocument const& doc);
    void updateAxisSettings(AxisData& axis, QJsonObject const& settings);
};

Q_DECLARE_METATYPE(Settings::LoadingError)

#endif // SETTINGS_H
