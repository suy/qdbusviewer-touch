#ifndef DBUSSERVICESMODEL_H
#define DBUSSERVICESMODEL_H

#include <QAbstractListModel>
#include <QDBusConnection>
#include <QStringList>

class DBusServicesModel : public QAbstractListModel
{
    Q_OBJECT
public:
	enum DBusRoles {
		ServiceRole = Qt::UserRole,
	};

    explicit DBusServicesModel(const QDBusConnection& connection, QObject *parent = 0);

    // For the model.
	QHash<int, QByteArray> roleNames() const Q_DECL_FINAL;
    QVariant data(const QModelIndex& i, int role) const Q_DECL_FINAL;
    int rowCount(const QModelIndex& i) const Q_DECL_FINAL;

private slots:
	void serviceRegistered(const QString& service);
	void serviceUnregistered(const QString &name);
    void serviceOwnerChanged(const QString &name, const QString &oldOwner,
                             const QString &newOwner);
    void refresh();
    // void refreshChildren();

private:
    QModelIndex findItem(const QString &name);

	QDBusConnection m_connection;
    QStringList m_services;

};

#endif // DBUSSERVICESMODEL_H
