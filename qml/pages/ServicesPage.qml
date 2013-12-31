import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        id: servicesList
        anchors.fill: parent
        model: sessionBusModel

        header: PageHeader { title: "D-Bus services" }

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable,
        // SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: servicesList.model.refresh()
            }
            MenuItem {
                text: "Session Bus"
                onClicked: servicesList.model = sessionBusModel
            }
            MenuItem {
                text: "System Bus"
                onClicked: servicesList.model = systemBusModel
            }
        }

        delegate: BackgroundItem {
            width: ListView.view.width
            Label {
                text: service
                font.pixelSize: Theme.fontSizeExtraSmall
                x: Theme.paddingSmall
                height: Theme.itemSizeSmall
                width: page.width - 2*Theme.paddingSmall
                truncationMode: TruncationMode.Fade
                color: Theme.primaryColor
            }
            onClicked: pageStack.push("MethodsPage.qml", {"service": service});
        }
    }
}

