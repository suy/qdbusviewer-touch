#include "dbusobjectmodel.h"
#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"

#include <QDebug>

DBusObjectModel::DBusObjectModel(QObject *parent)
    : QIdentityProxyModel(parent)
{
    QAbstractItemModel* model = static_cast<QAbstractItemModel*>(parent);
    Q_ASSERT_X(model, Q_FUNC_INFO, "The parent has to be a QAbstractItemModel");
    setSourceModel(model);
}

void DBusObjectModel::setObjectPath(QString path)
{
    m_objectPath = path;
}


QVariant DBusObjectModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::UserRole) {
        return QIdentityProxyModel::data(index, Qt::DisplayRole);
    }

    const QDBusItem *item = static_cast<QDBusItem *>(index.internalPointer());
    if (!item) {
        qWarning() << "No item at" << index;
        return QVariant();
    }

    if (role == Qt::UserRole) {
        return QIdentityProxyModel::data(index, Qt::DisplayRole);
    }

    if (role == Qt::UserRole+1) {
        QDBusModel* model = static_cast<QDBusModel*>(QObject::parent());
        QDBusModel::Type type = model->itemType(index);

        switch (type) {
        case QDBusModel::InterfaceItem:
            return "interface";
        case QDBusModel::PathItem:
            return "path";
        default:
            return "default";
        }
    }

    return QIdentityProxyModel::data(index, role);
}

