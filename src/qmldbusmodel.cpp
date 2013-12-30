#include "qmldbusmodel.h"
#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"

#include <QDBusConnection>

QmlDBusModel::QmlDBusModel(QObject* parent)
    : QSortFilterProxyModel(parent)
    , current(nullptr)
{
}

void QmlDBusModel::setService(QString service)
{
    delete current;
    current = new QDBusModel(service, QDBusConnection::systemBus());
    setSourceModel(current);
}

QVariant QmlDBusModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::UserRole) {
        return QSortFilterProxyModel::data(index, Qt::DisplayRole);
    }
    return QSortFilterProxyModel::data(index, role);
}
