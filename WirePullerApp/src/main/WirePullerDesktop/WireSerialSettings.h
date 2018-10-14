#ifndef WIRESERIALSETTINGS_H
#define WIRESERIALSETTINGS_H
#include <QGuiApplication>
#include "SerialSettings.h"


class WireSerialSettings : public SerialSettings
{
    Q_OBJECT
public:
    WireSerialSettings(QObject *parent = nullptr)
        : WireSerialSettings(true, parent)
    {
    }

    WireSerialSettings(bool storeOnDestroy, QObject *parent = nullptr)
        : SerialSettings ("pl.projektorion",
                          QGuiApplication::applicationName(),
                          storeOnDestroy,
                          parent)
    {

    }

    ~WireSerialSettings()
    {
    }
};

#endif // WIRESERIALSETTINGS_H
