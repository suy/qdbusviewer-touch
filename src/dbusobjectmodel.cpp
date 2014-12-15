#include "dbusobjectmodel.h"

#include <QDBusObjectPath>
#include <QDebug>

DBusObjectModel::DBusObjectModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void DBusObjectModel::componentComplete()
{
    Q_ASSERT_X(!m_service.isEmpty(), Q_FUNC_INFO, "A service name has to be set");
    Q_ASSERT_X(m_busType != QDBusConnection::SystemBus
            || m_busType != QDBusConnection::SessionBus, Q_FUNC_INFO,
            "Bus type has to be QDBusConnection::SessionBus or ::SystemBus");

    if (m_busType == QDBusConnection::SystemBus) {
        m_model = new QDBusModel(m_service, QDBusConnection::systemBus());
    } else {
        m_model = new QDBusModel(m_service, QDBusConnection::sessionBus());
    }
}

DBusObjectModel::~DBusObjectModel()
{
    delete m_model;
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

    if (role == SectionRole) {
        role = TypeRole;
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

