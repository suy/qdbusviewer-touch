#include "qmldbusmodel.h"

QmlDBusModel::QmlDBusModel(const QString &service, const QDBusConnection &connection) :
    QDBusModel(service, connection)
{
}
