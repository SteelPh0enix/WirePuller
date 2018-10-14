#include "SerialDeviceListModel.h"
#include <QSerialPortInfo>
#include <QByteArray>
#include <QVariant>
#include <QHash>
#include <QList>
#include <algorithm>


SerialDeviceListModel::SerialDeviceListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

SerialDeviceListModel::~SerialDeviceListModel()
{

}


int SerialDeviceListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return devices.size();
}

QVariant SerialDeviceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const auto row {index.row()};
    switch (role)
    {
    case Qt::DisplayRole:
        return devices[row];
    default:
        return QVariant();
    }
}

void SerialDeviceListModel::reload()
{
    emit beginResetModel();
    devices.clear();
    emit endResetModel();

    auto available {QSerialPortInfo::availablePorts()};
    devices.resize(available.count());

    emit beginInsertRows(QModelIndex(), 0, available.count() - 1);
    std::transform(std::begin(available), std::end(available),
                   std::begin(devices), [](const QSerialPortInfo &port)
    {
        return port.portName();
    });
    emit endInsertRows();
}

