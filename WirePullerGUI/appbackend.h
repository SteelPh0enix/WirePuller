#ifndef APPBACKEND_H
#define APPBACKEND_H

#include <QObject>
#include <QMap>
#include "settings.h"
#include "axisdatamodel.h"
#include "serialcommunicator.h"

class AppBackend : public QObject
{
    Q_OBJECT
public:
    explicit AppBackend(Settings* settings, QObject *parent = nullptr);

    AxisDataModel& xAxisData();
    AxisDataModel& wheelAxisData();
    AxisDataModel& breakerAxisData();

signals:

public slots:
    void setSerialPortName(QString const& name);

private:
    Settings* m_settings{nullptr};
    QMap<QString, AxisDataModel*> m_dataModels;
    SerialCommunicator m_communicator{this};
};

#endif // APPBACKEND_H
