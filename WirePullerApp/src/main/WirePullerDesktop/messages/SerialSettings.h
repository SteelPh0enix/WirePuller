#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QObject>

class SerialSettings : public QObject
{
    Q_OBJECT
public:
    explicit SerialSettings(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SERIALSETTINGS_H