import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800; height: 600

    property var selectedModel: sessionBusModel

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ExclusiveGroup { id: chosenBusGroup }
            ToolButton {
                text: qsTr("Session Bus")
                checkable: true
                checked: true
                onCheckedChanged: if (checked) selectedModel = sessionBusModel
                exclusiveGroup: chosenBusGroup
            }
            ToolButton {
                text: qsTr("System Bus")
                checkable: true
                onCheckedChanged: if (checked) selectedModel = systemBusModel
                exclusiveGroup: chosenBusGroup
            }
            ToolButton {
                text: qsTr("Refresh")
                onClicked: servicesList.model.refresh()
            }
            ToolButton {
                text: qsTr("Back")
                enabled: stack.currentItem !== servicesList
                onClicked: stack.pop();
            }
        }
    }

    StackView {
        id: stack
        anchors.fill: parent
        Component {
            id: objectView
            Rectangle {
                property alias text: label.text
                Text {
                    id: label
                    anchors.fill: parent
                }
            }
        }
        initialItem: TableView {
            id: servicesList
            headerVisible: false
            model: selectedModel
            onClicked: {
                stack.push({item: objectView, properties: {text: model.serviceAt(row)}})
            }
            TableViewColumn {
                role: "service"
            }
        }
    }
}
