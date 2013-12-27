#include <QDBusConnectionInterface>
#include <QDBusError>
#include <QDebug>

#include "dbusservicesmodel.h"

DBusServicesModel::DBusServicesModel(const QDBusConnection& connection,
                                     QObject *parent)
    : QAbstractListModel(parent)
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
    roles[ServiceRole] = "service";
    return roles;
}

QVariant DBusServicesModel::data(const QModelIndex& i, int role) const
{
    if (role != ServiceRole || i.row() > m_services.length()) {
        return QVariant();
    }
    return m_services.at(i.row());
}

int DBusServicesModel::rowCount(const QModelIndex&) const
{
    return m_services.count();
}




void DBusServicesModel::serviceRegistered(const QString& service)
{
    qDebug() << service;

    if (service == m_connection.baseService())
        return;

    this->insertRows(0, 1);
    this->setData(this->index(0, 0), service);
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
        this->removeRows(hit.row(), 1);
    else if (hit.isValid() && !oldOwner.isEmpty() && !newOwner.isEmpty()) {
        this->removeRows(hit.row(), 1);
        serviceRegistered(name);
    }
}

void DBusServicesModel::refresh()
{
    this->removeRows(0, this->rowCount(QModelIndex()));

    if (m_connection.isConnected()) {
        const QStringList names = m_connection.interface()->registeredServiceNames();
        m_services = names;
        // this->setStringList(serviceNames);
        // for (const auto& name : names) {
        //     qDebug() << name;
        //
        // }
    }
}

// void DBusServicesModel::refreshChildren()
// {
//     QDBusModel *model = qobject_cast<DBusServicesModel *>(tree->model());
//     if (!model)
//         return;
//     model->refresh(tree->currentIndex());
// }

