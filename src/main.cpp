#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>
#include <QQuickView>

#include "src/dbusservicesmodel.h"

// FIXME: Caution, Q_OS_SAILFISH is a non-"standard" (Qt provided) define.
#ifdef Q_OS_SAILFISH
#include <sailfishapp.h>
#endif

int main(int argc, char* argv[])
{
#ifdef Q_OS_SAILFISH
    QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());
    DBusServicesModel servicesModel(QDBusConnection::systemBus());
    view->rootContext()->setContextProperty("servicesModel", &servicesModel);
    view->setSource(SailfishApp::pathTo("qml/dbusviewertouch.qml"));
    view->show();
#else
    QGuiApplication application(argc, argv);
    QQmlApplicationEngine engine;
    DBusServicesModel servicesModel(QDBusConnection::systemBus());
    engine.rootContext()->setContextProperty(QStringLiteral("servicesModel"), &servicesModel);
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
