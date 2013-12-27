import QtQuick 2.1
import QtQuick.Controls 1.0

ApplicationWindow {
    ListView {
        anchors.fill: parent
        model: servicesModel
        delegate: Text {
            text: service
        }
    }

    width: 800
    height: 600
}
