#ifndef DBUSOBJECTMODEL_H
#define DBUSOBJECTMODEL_H

#include <QIdentityProxyModel>

class DBusObjectModel : public QIdentityProxyModel
{
    Q_OBJECT
public:
    explicit DBusObjectModel(QObject *parent = 0);
    void setObjectPath(QString path);

    QVariant data(const QModelIndex& index, int role) const;
    QHash<int, QByteArray> roleNames() const {
        QHash<int, QByteArray> roles;
        roles[Qt::UserRole+0] = "name";
        roles[Qt::UserRole+1] = "type";
        return roles;
    }

private:
    QString m_objectPath;

};

#endif // DBUSOBJECTMODEL_H
