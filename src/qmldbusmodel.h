#ifndef QMLDBUSMODEL_H
#define QMLDBUSMODEL_H

#include <QSortFilterProxyModel>

class QDBusModel;

class QmlDBusModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QmlDBusModel(QObject* parent = 0);

    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[Qt::UserRole] = "info";
        return roles;
    }
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    Q_INVOKABLE void setService(QString service);

private:
    QDBusModel* current;


};

#endif // QMLDBUSMODEL_H
