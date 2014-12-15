import QtQuick 2.1
import QtQml.Models 2.1
import My.DBusObjectModel 0.1

ListView {
    id: root

    property alias service: dbusObjectModel.service
    property alias busType: dbusObjectModel.busType

    model: DelegateModel {
        model: DBusObjectModel {
            id: dbusObjectModel
        }
        delegate: Text {text: name}
    }
}
