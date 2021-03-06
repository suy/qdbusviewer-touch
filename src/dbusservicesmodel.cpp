#include <QDBusConnectionInterface>
#include <QDBusError>
#include <QLoggingCategory>

#include "dbusservicesmodel.h"

Q_LOGGING_CATEGORY(LCM, "app.servicesmodel.innermodel")
Q_LOGGING_CATEGORY(LCR, "app.servicesmodel.registration")

DBusServicesModel::DBusServicesModel(const QDBusConnection& connection,
                                     QObject *parent)
    : QStringListModel(parent)
    , m_connection(connection)
{
    QDBusConnectionInterface *iface = m_connection.interface();
    connect(iface, SIGNAL(serviceRegistered(QString)),
            this, SLOT(serviceRegistered(QString)));
    connect(iface, SIGNAL(serviceUnregistered(QString)),
            this, SLOT(serviceUnregistered(QString)));
    connect(iface, SIGNAL(serviceOwnerChanged(QString,QString,QString)),
            this, SLOT(serviceOwnerChanged(QString,QString,QString)));
    refresh();
}

//
// For the model.
//
QHash<int, QByteArray> DBusServicesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "service"; // Service name, e.g. ':1.8'.
    roles[Qt::UserRole] = "myself";  // Whether this is the service of the app.
    return roles;
}


void DBusServicesModel::serviceRegistered(const QString& service)
{
    qCDebug(LCR) << service;
    if (service == m_connection.baseService()) {
        Q_ASSERT_X(stringList().contains(service), Q_FUNC_INFO, "Should already be there");
        return;
    }
    insertRows(0, 1);
    setData(this->index(0, 0), service, Qt::DisplayRole);
}

QModelIndex DBusServicesModel::findItem(const QString &name)
{
    qCDebug(LCM) << name;

    QModelIndexList hits = this->match(this->index(0, 0), Qt::DisplayRole, name);
    if (hits.isEmpty())
        return QModelIndex();

    return hits.first();
}

void DBusServicesModel::serviceUnregistered(const QString &name)
{
    qCDebug(LCR) << name;

    QModelIndex hit = findItem(name);
    if (!hit.isValid())
        return;
    this->removeRows(hit.row(), 1);
}

void DBusServicesModel::serviceOwnerChanged(const QString &name,
                                            const QString &oldOwner,
                                            const QString &newOwner)
{
    qCDebug(LCR) << name << oldOwner << newOwner;

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
    // Usual case: the "service" property on the QML delegate.
    if (role == Qt::DisplayRole) {
        return QStringListModel::data(i, role);
    }

    // The "myself" property when true.
    if (i.data(Qt::DisplayRole).toString() == m_connection.baseService()
        && role == Qt::UserRole)
    {
        return QVariant(true);
    }

    // All other cases.
    return QVariant();
}
