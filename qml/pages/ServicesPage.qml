import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    allowedOrientations: Orientation.All

    SilicaListView {
        anchors.fill: parent
        model: servicesModel

        header: PageHeader { title: "D-Bus services" }

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable,
        // SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: servicesModel.refresh()
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
        }
    }
}

