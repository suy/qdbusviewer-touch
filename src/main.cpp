#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

#include "src/dbusservicesmodel.h"

int main(int argc, char* argv[])
{
	QGuiApplication application(argc, argv);
    qSetMessagePattern(QStringLiteral("["
        "%{if-debug}D%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}"
        "] %{function}\n    %{message}"
    ));

    DBusServicesModel servicesModel(QDBusConnection::systemBus());
	QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("servicesModel"), &servicesModel);
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
}
