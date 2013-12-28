import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    SilicaListView {
        anchors.fill: parent

        header: PageHeader { title: "D-Bus services" }

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable,
        // SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: servicesModel.refresh()
            }
            MenuItem {
                text: "Show Page 2"
                onClicked: pageStack.push(Qt.resolvedUrl("SecondPage.qml"))
            }
        }

        model: servicesModel
        delegate: ListItem {
            Label {
                text: service
                width: ListView.view.width
                height: Theme.itemSizeSmall
            }
        }
    }
}

