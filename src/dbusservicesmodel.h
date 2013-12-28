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
    int rowCount(const QModelIndex& i = QModelIndex()) const Q_DECL_FINAL;
    // For the model as well, but optional.
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_FINAL;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) Q_DECL_FINAL;
    bool setData(const QModelIndex& i, const QVariant& data, int role = Qt::EditRole) Q_DECL_FINAL;

public slots:
    void refresh();

private slots:
	void serviceRegistered(const QString& service);
	void serviceUnregistered(const QString &name);
    void serviceOwnerChanged(const QString &name, const QString &oldOwner,
                             const QString &newOwner);
    // void refreshChildren();

private:
    QModelIndex findItem(const QString &name);

	QDBusConnection m_connection;
    QStringList m_services;

};

#endif // DBUSSERVICESMODEL_H
