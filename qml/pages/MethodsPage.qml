import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    allowedOrientations: Orientation.All

    property string service

    SilicaListView {
        anchors.fill: parent
        model: servicesModel

        header: PageHeader { title: service }

        delegate: BackgroundItem {
            width: ListView.view.width
            Label {
                text: "foo"
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



