#include "dbusobjectmodel.h"
#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"

#include <QDebug>
#include <QDBusObjectPath>

DBusObjectModel::DBusObjectModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_model = static_cast<QDBusModel*>(parent);
    Q_ASSERT_X(m_model, Q_FUNC_INFO, "The parent has to be a QDBusModel");
}

void DBusObjectModel::setObjectPath(QString path)
{
    m_index = m_model->findObject(QDBusObjectPath(path));
}


int DBusObjectModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return m_model->rowCount(m_index);
}


QVariant DBusObjectModel::data(const QModelIndex& index, int role) const
{
    QModelIndex mapped = m_model->index(index.row(), index.column(), m_index);

    if (!mapped.isValid()) {
        qWarning() << "Can't map" << index << "to our" << m_index;
        return QVariant();
    }

    if (role == NameRole) {
        return m_model->data(mapped, Qt::DisplayRole);
    }

    if (role == PathRole) {
        return m_model->dBusPath(mapped);
    }

    // TODO: use an enum registered in QML.
    if (role == TypeRole) {
        QDBusModel::Type type = m_model->itemType(mapped);
        switch (type) {
        case QDBusModel::InterfaceItem:
            return "interface";
        case QDBusModel::PathItem:
            return "path";
        case QDBusModel::MethodItem:
            return "method";
        case QDBusModel::SignalItem:
            return "signal";
        case QDBusModel::PropertyItem:
            return "property";
        default:
            return "default";
        }
    }

    return m_model->data(mapped, role);
}

