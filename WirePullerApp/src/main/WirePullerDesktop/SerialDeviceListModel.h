#ifndef SERIALDEVICELISTMODEL_H
#define SERIALDEVICELISTMODEL_H
#include <QAbstractListModel>
#include <QVector>
#include <QString>

class SerialDeviceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum SerialDeviceRoles {
        PortNameRole = Qt::UserRole + 1
    };

    SerialDeviceListModel(QObject *parent = nullptr);
    ~SerialDeviceListModel() override;

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE void reload();


private:
    QVector<QString> devices;
};

#endif // SERIALDEVICELISTMODEL_H
