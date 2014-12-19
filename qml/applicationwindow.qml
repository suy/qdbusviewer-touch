import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0
import My.DBus 0.1

ApplicationWindow {
    width: 800; height: 600

    property int selectedBus: DBus.SessionBus

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ExclusiveGroup { id: chosenBusGroup }
            ToolButton {
                text: qsTr("Session Bus")
                checkable: true
                checked: true
                onCheckedChanged: if (checked) selectedBus = DBus.SessionBus
                exclusiveGroup: chosenBusGroup
            }
            ToolButton {
                text: qsTr("System Bus")
                checkable: true
                onCheckedChanged: if (checked) selectedBus = DBus.SystemBus
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
            DBusObjectView {}
        }
        initialItem: TableView {
            id: servicesList
            model: selectedBus === DBus.SessionBus? sessionBusModel : systemBusModel;
            onActivated: stack.push({
                    item: objectView,
                    properties: {
                        service: model.serviceAt(row),
                        busType: selectedBus
                    }
                })
            style: TableViewStyle {
                activateItemOnSingleClick: true
            }

            TableViewColumn {
                role: "myself"
                title: qsTr("myself")
                width: 15
                delegate: Rectangle {
                    color: styleData.value ? "gray" : "transparent"
                }
            }

            TableViewColumn {
                role: "service"
                title: qsTr("Service name")
            }
        }
    }
}
