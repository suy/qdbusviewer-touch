import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    allowedOrientations: Orientation.All

    property bool sessionBus: true

    SilicaListView {
        id: servicesList
        anchors.fill: parent
        model: sessionBusModel

        header: PageHeader { title: "D-Bus services" }

        ViewPlaceholder {
            enabled: servicesList.count === 0
            text: "No services found"
        }

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable,
        // SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: "Refresh"
                onClicked: servicesList.model.refresh()
            }
            MenuItem {
                text: "Session Bus"
                onClicked: {
                    servicesList.model = sessionBusModel;
                    sessionBus=true;
                }
            }
            MenuItem {
                text: "System Bus"
                onClicked: {
                    servicesList.model = systemBusModel;
                    sessionBus=false;
                }
            }
        }

        delegate: BackgroundItem {
            id: backgroundItem
            width: ListView.view.width
            Label {
                text: service
                x: Theme.paddingSmall
                anchors.verticalCenter: parent.verticalCenter
                height: Theme.itemSizeSmall
                width: page.width - 2*Theme.paddingSmall
                font.pixelSize: Theme.fontSizeExtraSmall
                font.bold: myself === true
                color: myself === true? Theme.secondaryColor: Theme.primaryColor
                truncationMode: TruncationMode.Fade
            }
            onClicked: {
                pageStack.push("MethodsPage.qml",
                    {"service": service, "sessionBus": sessionBus}
                );
            }
            ListView.onAdd:    AddAnimation    { target: backgroundItem }
            ListView.onRemove: RemoveAnimation { target: backgroundItem }
        }
    }
}

