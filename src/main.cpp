#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickView>
#include <QQuickWindow>

#include "src/dbusservicesmodel.h"
#include "src/helper.h"
#include "src/dbusobjectmodel.h"

#ifdef OS_SAILFISH
#include <sailfishapp.h>
#endif

int main(int argc, char* argv[])
{
    qSetMessagePattern(QStringLiteral("["
        "%{if-debug}D%{endif}%{if-warning}W%{endif}"
        "%{if-critical}C%{endif}%{if-fatal}F%{endif}"
        "] %{function}\n    %{message}"
    ));
    qmlRegisterType<DBusObjectModel>("My.DBusObjectModel", 0, 1, "DBusObjectModel");
    Helper helper;

#ifdef OS_SAILFISH
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    QQmlContext* context = view->rootContext();
#else // Desktop for now only.
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* context = engine.rootContext();
#endif

    DBusServicesModel systemBusModel(QDBusConnection::systemBus());
    DBusServicesModel sessionBusModel(QDBusConnection::sessionBus());

    context->setContextProperty(QStringLiteral("helper"), &helper);
    context->setContextProperty(QStringLiteral("systemBusModel"), &systemBusModel);
    context->setContextProperty(QStringLiteral("sessionBusModel"), &sessionBusModel);

#ifdef OS_SAILFISH
    view->setSource(SailfishApp::pathTo("qml/harbour-dbusviewertouch.qml"));
    view->show();

    QObject::connect(view->rootObject(), SIGNAL(backToStart()),
                    &helper, SLOT(onBackToStart()));
    return application->exec();
#else // Desktop for now only.
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
