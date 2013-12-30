import QtQuick 2.0
import Sailfish.Silica 1.0
import My.QmlDBusModel 0.1


Page {
    id: page
    allowedOrientations: Orientation.All

    property string service

    Component.onCompleted: dbusmodel.setService(service);

    SilicaListView {
        anchors.fill: parent
        model: QmlDBusModel {
            id: dbusmodel
        }

        header: PageHeader { title: service }

        delegate: BackgroundItem {
            width: ListView.view.width
            Label {
                text: info
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



