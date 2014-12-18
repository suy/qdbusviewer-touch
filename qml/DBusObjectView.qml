import QtQuick 2.1
import QtQml.Models 2.1
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.0

import My.DBusObjectModel 0.1

Item {
    property alias service: dbusObjectModel.service
    property alias busType: dbusObjectModel.busType
    property string currentObjectPath: "/"

    ColumnLayout {
        anchors.fill: parent

        Label {
            Layout.fillWidth: true
            text: qsTr("Showing object: %1").arg(currentObjectPath)
        }

        TableView {
            Layout.fillHeight: true
            Layout.fillWidth: true
            TableViewColumn {role: "name"; visible: false}

            section {
                property: 'section'
                delegate: Text {
                    text: section; font.bold: true
                }
            }

            model: DelegateModel {
                model: DBusObjectModel {
                    id: dbusObjectModel
                }
                delegate: Label {text: name}
            }
        }
    }
}
