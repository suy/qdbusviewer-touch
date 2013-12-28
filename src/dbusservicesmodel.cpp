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

//
// For the model as well, but optional.
//
bool DBusServicesModel::insertRows(int row, int count, const QModelIndex&)
{
    qDebug() << "row" << row << "count" << count << "size" << m_services.size();
    qDebug() << "before" << m_services;
    beginInsertRows(QModelIndex(), row, row+count);
    m_services.append(QString());
    endInsertRows();
    qDebug() << "after" << m_services;
    return true;
}

bool DBusServicesModel::removeRows(int row, int count, const QModelIndex&)
{
    qDebug() << "row" << row << "count" << count << "size" << m_services.size();
    qDebug() << "before" << m_services;
    beginRemoveRows(QModelIndex(), row, row+count);
    for (int i=0; i < count; i++) {
        m_services.removeAt(row+i);
    }
    endRemoveRows();
    qDebug() << "after" << m_services;
    return true;
}

bool DBusServicesModel::setData(const QModelIndex& i, const QVariant& data, int role)
{
    if (role == ServiceRole) {
        QString s = m_services.at(i.row());
        s = data.toString();
        return true;
    }
    return false;
}


void DBusServicesModel::serviceRegistered(const QString& service)
{
    qDebug() << service;

    if (service == m_connection.baseService())
        return;

    this->insertRows(0, 1);
    this->setData(this->index(0, 0), service, ServiceRole);
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
    qDebug() << "before" << m_services;
    beginRemoveRows(QModelIndex(), 0, rowCount());
    this->removeRows(0, this->rowCount());
    endRemoveRows();

    if (m_connection.isConnected()) {
        const QStringList names = m_connection.interface()->registeredServiceNames();
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_services = names;
        endInsertRows();
        // this->setStringList(serviceNames);
        // for (const auto& name : names) {
        //     qDebug() << name;
        //
        // }
    }
    qDebug() << "after" << m_services;
}

// void DBusServicesModel::refreshChildren()
// {
//     QDBusModel *model = qobject_cast<DBusServicesModel *>(tree->model());
//     if (!model)
//         return;
//     model->refresh(tree->currentIndex());
// }

