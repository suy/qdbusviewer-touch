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
        }
    }

    StackView {
        anchors.fill: parent
        TableView {
            id: servicesList
            anchors.fill: parent
            headerVisible: false
            model: selectedModel
            onClicked: console.log(model, row)
            TableViewColumn {
                role: "service"
            }
        }
    }
}
