#ifndef DBUSSERVICESMODEL_H
#define DBUSSERVICESMODEL_H

#include <QStringListModel>
#include <QDBusConnection>
#include <QStringList>

class DBusServicesModel : public QStringListModel
{
    Q_OBJECT
public:
    explicit DBusServicesModel(const QDBusConnection& connection, QObject *parent = 0);

    // For the model.
	QHash<int, QByteArray> roleNames() const Q_DECL_FINAL;
    QVariant data(const QModelIndex& i, int role) const Q_DECL_FINAL;

public slots:
    void refresh();

private slots:
	void serviceRegistered(const QString& service);
	void serviceUnregistered(const QString &name);
    void serviceOwnerChanged(const QString &name, const QString &oldOwner,
                             const QString &newOwner);

private:
    QModelIndex findItem(const QString &name);

	QDBusConnection m_connection;

};

#endif // DBUSSERVICESMODEL_H
