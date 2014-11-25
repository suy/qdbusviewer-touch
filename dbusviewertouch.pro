QT = core dbus gui quick xml
TARGET = dbusviewertouch
CONFIG += c++11

SOURCES = src/main.cpp src/dbusservicesmodel.cpp \
    qttools/src/qdbus/qdbusviewer/qdbusmodel.cpp \
    src/dbusobjectmodel.cpp \
    src/helper.cpp
HEADERS = src/dbusservicesmodel.h \
    qttools/src/qdbus/qdbusviewer/qdbusmodel.h \
    src/dbusobjectmodel.h \
    src/helper.h

RESOURCES = dbusviewertouch.qrc

#
# Sailfish OS dependent.
#
packagesExist(sailfishapp) {
    message(Building for Sailfish OS)
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
	# SOURCES += src/dbusviewertouch.cpp
    DEFINES += OS_SAILFISH

    # QML files.
	OTHER_FILES += qml/dbusviewertouch.qml \
        qml/pages/ServicesPage.qml \
        qml/pages/ObjectPage.qml \

    # Deployment/packaging.
    OTHER_FILES += \
		rpm/dbusviewertouch.spec \
		rpm/dbusviewertouch.yaml \
		dbusviewertouch.desktop
}
## FIXME: a better fallback for "desktop" cases?
else {
    # SOURCES += src/main.cpp

    OTHER_FILES += \
        qml/applicationwindow.qml
}

