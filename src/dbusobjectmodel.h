#ifndef DBUSOBJECTMODEL_H
#define DBUSOBJECTMODEL_H

#include <QAbstractListModel>

class QDBusModel;

class DBusObjectModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {NameRole = Qt::UserRole+1, TypeRole, PathRole};

    explicit DBusObjectModel(QObject *parent = 0);
    void setObjectPath(QString path);

    QVariant data(const QModelIndex& index, int role) const Q_DECL_FINAL;
    QHash<int, QByteArray> roleNames() const Q_DECL_FINAL {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[TypeRole] = "type";
        roles[PathRole] = "path";
        return roles;
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_FINAL;

private:
    QPersistentModelIndex m_index;
    QDBusModel* m_model;
};

#endif // DBUSOBJECTMODEL_H
