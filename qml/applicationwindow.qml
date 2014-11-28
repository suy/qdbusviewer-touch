import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800; height: 600

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ExclusiveGroup { id: chosenBusGroup }
            ToolButton {
                text: qsTr("Session Bus")
                checkable: true
                checked: true
                exclusiveGroup: chosenBusGroup
            }
            ToolButton {
                text: qsTr("System Bus")
                checkable: true
                exclusiveGroup: chosenBusGroup
            }
            ToolButton {
                text: "Refresh"
                onClicked: servicesList.model.refresh()
            }
        }
    }

    TabView {
        anchors.fill: parent
        Tab {
            title: "Services"
            TableView {
                id: servicesList
                anchors.fill: parent
                headerVisible: false
                model: sessionBusModel
                onClicked: console.log(model, row)
                TableViewColumn {
                    role: "service"
                }
            }
        }
    }
}
