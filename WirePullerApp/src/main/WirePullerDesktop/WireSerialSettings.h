#ifndef WIRESERIALSETTINGS_H
#define WIRESERIALSETTINGS_H
#include <QGuiApplication>
#include "SerialSettings.h"


class WireSerialSettings : public SerialSettings
{
    Q_OBJECT
public:
    WireSerialSettings(QObject *parent = nullptr)
        : SerialSettings ("pl.projektorion", QGuiApplication::applicationName(), parent)
    {
    }

    ~WireSerialSettings()
    {
    }
};

#endif // WIRESERIALSETTINGS_H
