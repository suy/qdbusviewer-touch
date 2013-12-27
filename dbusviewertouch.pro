QT = core dbus gui quick xml
TARGET = dbusviewertouch
CONFIG += c++11

SOURCES = src/main.cpp \
    src/dbusservicesmodel.cpp

RESOURCES = dbusviewertouch.qrc

#
# Sailfish OS dependent.
#
packagesExist(sailfishapp) {
	CONFIG += sailfishapp

	# From the template provided by the Sailfish SDK:
	# <blockquote>
	# NOTICE: name defined in TARGET has a corresponding QML filename.
	#         If name defined in TARGET is changed, following needs to be
	#         done to match new name:
	#         - corresponding QML filename must be changed
	#         - desktop icon filename must be changed
	#         - desktop filename must be changed
	#         - icon definition filename in desktop file must be changed
	# </blockquote>
	# FIXME: prepend "harbour-" to all the mentioned thingies.
	TARGET = dbusviewertouch

	# Where main() is provided.
	SOURCES += src/dbusviewertouch.cpp

	OTHER_FILES += qml/dbusviewertouch.qml \
		qml/cover/CoverPage.qml \
		qml/pages/SecondPage.qml \
		rpm/dbusviewertouch.spec \
		rpm/dbusviewertouch.yaml \
		dbusviewertouch.desktop \
		qml/pages/ServicesPage.qml
}


SOURCES += qttools/src/qdbus/qdbusviewer/qdbusmodel.cpp \
    src/qmldbusmodel.cpp

HEADERS += qttools/src/qdbus/qdbusviewer/qdbusmodel.h \
    src/qmldbusmodel.h \
    src/dbusservicesmodel.h

OTHER_FILES += \
    qml/applicationwindow.qml


