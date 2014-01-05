#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickView>

// Argh, do I need the whole module for qmlRegisterType?? Insane, but seems so.
#include <QtQml>

#include "src/dbusservicesmodel.h"
#include "src/helper.h"
#include "src/dbusobjectmodel.h"

// FIXME: Caution, Q_OS_SAILFISH is a non-"standard" (Qt provided) define.
#ifdef Q_OS_SAILFISH
#include <sailfishapp.h>
#endif

int main(int argc, char* argv[])
{
    qmlRegisterType<DBusObjectModel>("My.DBusObjectModel", 0, 1, "DBusObjectModel");
    Helper helper;
#ifdef Q_OS_SAILFISH
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    DBusServicesModel systemBusModel(QDBusConnection::systemBus());
    DBusServicesModel sessionBusModel(QDBusConnection::sessionBus());
    view->rootContext()->setContextProperty("systemBusModel", &systemBusModel);
    view->rootContext()->setContextProperty("sessionBusModel", &sessionBusModel);
    view->rootContext()->setContextProperty("helper", &helper);
    view->setSource(SailfishApp::pathTo("qml/dbusviewertouch.qml"));
    view->show();

    QObject::connect(view->rootObject(), SIGNAL(backToStart()),
                    &helper, SLOT(onBackToStart()));

#else
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;
    DBusServicesModel systemBusModel(QDBusConnection::systemBus());
    DBusServicesModel sessionBusModel(QDBusConnection::sessionBus());
    engine.rootContext()->setContextProperty(QStringLiteral("systemBusModel"), &systemBusModel);
    engine.rootContext()->setContextProperty(QStringLiteral("sessionBusModel"), &sessionBusModel);
    engine.rootContext()->setContextProperty("helper", &helper);
#endif

    qSetMessagePattern(QStringLiteral("["
        "%{if-debug}D%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}"
        "] %{function}\n    %{message}"
    ));

#ifdef Q_OS_SAILFISH
    return application->exec();
#else
    engine.load(QUrl("qrc:/qml/applicationwindow.qml"));

    // There is only one root object in our QML file.
    QObject* interface = engine.rootObjects().first();
    QQuickWindow* window = qobject_cast<QQuickWindow *>(interface);
    if ( !window ) {
        qCritical("The root element of the QML file is not a Window element");
        return -1;
    }
    window->show();

    return application.exec();
#endif
}
