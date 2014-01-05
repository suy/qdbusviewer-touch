#include "dbusobjectmodel.h"

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
    return QIdentityProxyModel::data(index, role);
}

