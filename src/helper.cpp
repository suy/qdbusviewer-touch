#include "qttools/src/qdbus/qdbusviewer/qdbusmodel.h"
#include "dbusobjectmodel.h"
#include "helper.h"

#include <QDBusConnection>
#include <QDebug>

Helper::Helper(QObject* parent)
    : QObject(parent)
    , m_model(nullptr)
{
}

Helper::~Helper()
{
    delete m_model;
}

DBusObjectModel* Helper::makeModel(bool session, QString service, QString objectPath)
{
    qDebug() << session << service << objectPath;

    if (m_model == nullptr) {
        if (session) {
            m_model = new QDBusModel(service, QDBusConnection::sessionBus());
        } else {
            m_model = new QDBusModel(service, QDBusConnection::systemBus());
        }
    }

    DBusObjectModel* model = new DBusObjectModel(m_model);
    model->setObjectPath(objectPath);

    return model;
}

void Helper::onBackToStart()
{
    delete m_model;
    m_model = nullptr;
}
