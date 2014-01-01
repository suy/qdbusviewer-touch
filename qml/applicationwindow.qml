import QtQuick 2.1
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    width: 800; height: 600

    property bool sessionBus: true

    toolBar: ToolBar {
        RowLayout {
            anchors.fill: parent
            ToolButton {
                text: "Session Bus"
                id: sessionBusButton
                checkable: true
                checked: sessionBus
                onClicked: {
                    servicesList.model = sessionBusModel;
                    sessionBus=true;
                    checked=sessionBus
                    systemBusButton.checked=false;
                }
            }
            ToolButton {
                text: "System Bus"
                id: systemBusButton
                checkable: true
                checked: !sessionBus
                onClicked: {
                    servicesList.model = systemBusModel;
                    sessionBus=false;
                    checked=!sessionBus
                    sessionBusButton.checked=false;
                }
            }
            ToolButton {
                text: "Refresh"
                onClicked: servicesList.model.refresh()
            }
        }
    }

    TableView {
        id: servicesList
        anchors.fill: parent
        headerVisible: false
        model: sessionBusModel
        TableViewColumn {
            role: "service"
        }
    }
}
