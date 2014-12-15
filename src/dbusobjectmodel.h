#ifndef DBUSOBJECTMODEL_H
#define DBUSOBJECTMODEL_H

#include <QAbstractListModel>
#include <QDBusConnection>
#include <QQmlParserStatus>

#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"

class DBusObjectModel : public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(QString service READ service WRITE setService)
    Q_PROPERTY(QDBusConnection::BusType busType READ busType WRITE setConnection)
public:
    enum Roles {NameRole = Qt::UserRole+1, TypeRole, PathRole, SectionRole};

    explicit DBusObjectModel(QObject *parent = 0);
    ~DBusObjectModel();

    // Pure virtual functions from QQmlParserStatus.
    void classBegin() {}
    void componentComplete();

    QString service() {return m_service;}
    void setService(const QString& service) { m_service = service; }
    QDBusConnection::BusType busType() { return m_busType; }
    void setConnection(QDBusConnection::BusType busType) {
        m_busType = busType;
    }

    void setObjectPath(QString path);

    QVariant data(const QModelIndex& index, int role) const Q_DECL_FINAL;
    QHash<int, QByteArray> roleNames() const Q_DECL_FINAL {
        QHash<int, QByteArray> roles;
        roles[NameRole] = "name";
        roles[TypeRole] = "type";
        roles[SectionRole] = "section";
        roles[PathRole] = "path";
        return roles;
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_FINAL;

private:
    QPersistentModelIndex m_index;
    QDBusModel* m_model;
    QString m_service;
    QDBusConnection::BusType m_busType;
};

#endif // DBUSOBJECTMODEL_H
