import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800; height: 600

    property variant sessionBus: true

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Session Bus"
                onClicked: {
                    servicesList.model = sessionBusModel;
                    sessionBus=true;
                }
            }
            ToolButton {
                text: "System Bus"
                onClicked: {
                    servicesList.model = systemBusModel;
                    sessionBus=false;
                }
            }
            ToolButton {
                text: "Refresh"
                onClicked: servicesList.model.refresh()
            }
        }
    }

    ListView {
        id: servicesList
        anchors.fill: parent
        model: sessionBusModel
        delegate: Text {
            text: service
        }
    }
}
