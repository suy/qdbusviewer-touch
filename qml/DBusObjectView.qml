import QtQuick 2.1
import QtQml.Models 2.1
import My.DBus 0.1

ListView {
    id: root

    property string serviceName
    property var dbusConnection

    model: DelegateModel {
        id: delegateModel
        model: 1
        delegate: Text {text: serviceName}
    }
}
