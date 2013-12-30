#ifndef QMLDBUSMODEL_H
#define QMLDBUSMODEL_H

#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"

class QmlDBusModel : public QDBusModel
{
    Q_OBJECT
public:
    explicit QmlDBusModel(const QString &service, const QDBusConnection &connection);

signals:

public slots:

};

#endif // QMLDBUSMODEL_H
