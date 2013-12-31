import QtQuick 2.0
import Sailfish.Silica 1.0
import My.QmlDBusModel 0.1


Page {
    id: page
    allowedOrientations: Orientation.All

    property string service
    property bool sessionBus

    Component.onCompleted: dbusmodel.setService(service);

    SilicaListView {
        anchors.fill: parent
        header: PageHeader { title: service }

        model: QmlDBusModel {
            id: dbusmodel
        }

        ViewPlaceholder {
            enabled: parent.count === 0
            text: "No objects or interfaces found"
        }

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

