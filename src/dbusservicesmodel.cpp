#ifndef DEBUG_DBUSSERVICESMODEL
#define QT_NO_DEBUG_OUTPUT
#endif

#include <QDBusConnectionInterface>
#include <QDBusError>
#include <QDebug>

#include "dbusservicesmodel.h"

DBusServicesModel::DBusServicesModel(const QDBusConnection& connection,
                                     QObject *parent)
    : QStringListModel(parent)
    , m_connection(connection)
{
    if (m_connection.isConnected()) {
        QDBusConnectionInterface *iface = m_connection.interface();
        connect(iface, SIGNAL(serviceRegistered(QString)),
                this, SLOT(serviceRegistered(QString)));
        connect(iface, SIGNAL(serviceUnregistered(QString)),
                this, SLOT(serviceUnregistered(QString)));
        connect(iface, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
                this, SLOT(serviceOwnerChanged(QString,QString,QString)));
    } else {
        qCritical() << QStringLiteral("Can't connect to D-Bus!")
                    << m_connection.lastError().message();
    }
    refresh();
}

//
// For the model.
//
QHash<int, QByteArray> DBusServicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "service";
    roles[MyselfRole] = "myself";
    return roles;
}


void DBusServicesModel::serviceRegistered(const QString& service)
{
    qDebug() << service;

    if (service == m_connection.baseService())
        return;

    insertRows(0, 1);
    setData(this->index(0, 0), service, Qt::DisplayRole);
}

QModelIndex DBusServicesModel::findItem(const QString &name)
{
    qDebug() << name;

    QModelIndexList hits = this->match(this->index(0, 0), Qt::DisplayRole, name);
    if (hits.isEmpty())
        return QModelIndex();

    return hits.first();
}

void DBusServicesModel::serviceUnregistered(const QString &name)
{
    qDebug() << name;

    QModelIndex hit = findItem(name);
    if (!hit.isValid())
        return;
    this->removeRows(hit.row(), 1);
}

void DBusServicesModel::serviceOwnerChanged(const QString &name, const QString &oldOwner,
                                            const QString &newOwner)
{
    qDebug() << name << oldOwner << newOwner;

    QModelIndex hit = findItem(name);

    if (!hit.isValid() && oldOwner.isEmpty() && !newOwner.isEmpty())
        serviceRegistered(name);
    else if (hit.isValid() && !oldOwner.isEmpty() && newOwner.isEmpty())
        removeRows(hit.row(), 1);
    else if (hit.isValid() && !oldOwner.isEmpty() && !newOwner.isEmpty()) {
        removeRows(hit.row(), 1);
        serviceRegistered(name);
    }
}

void DBusServicesModel::refresh()
{
    if (!m_connection.isConnected()) {
        qCritical() << "D-Bus connection lost. Can't refresh";
        return;
    }

    const QStringList names = m_connection.interface()->registeredServiceNames();
    setStringList(names);
}

QVariant DBusServicesModel::data(const QModelIndex& i, int role) const
{
    if (role == Qt::DisplayRole) {
        return QStringListModel::data(i, role);
    }

    if (i.data(Qt::DisplayRole).toString() == m_connection.baseService()
        && role == MyselfRole)
    {
        qDebug() << "Found myself" << m_connection.baseService();
        return QVariant(true);
    }

    return QVariant();
}
