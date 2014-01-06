import QtQuick 2.0
import Sailfish.Silica 1.0


Page {
    id: page
    allowedOrientations: Orientation.All

    property bool sessionBus
    property string service
    property string objectPath

    Component.onCompleted: {
        console.log("ObjectPage for", (sessionBus? "session": "system"), "bus");
        console.log(service, objectPath);
        var m = helper.makeModel(sessionBus, service, objectPath);
        console.log(m);
        contents.model = m;
    }

    SilicaListView {
        id: contents
        anchors.fill: parent
        header: PageHeader { title: service }

        // Undocumented?
        section {
            property: 'section'
            delegate: SectionHeader {
                text: section
            }
        }

        ViewPlaceholder {
            enabled: parent.count === 0
            text: "No objects or interfaces found"
        }

        delegate: BackgroundItem {
            width: ListView.view.width
            Label {
                // text: name + " (" + type + ")"
                text: {
                    if (type === "interface") {
                        return name;
                    } else if (type === "path") {
                        return path;
                    }
                }
                font.pixelSize: Theme.fontSizeExtraSmall
                x: Theme.paddingSmall
                height: Theme.itemSizeSmall
                width: page.width - 2*Theme.paddingSmall
                truncationMode: TruncationMode.Fade
                horizontalAlignment: type === "path"? Text.AlignRight : Text.AlignLeft
                color: Theme.primaryColor
            }
            onClicked: {
                console.log(name, type);
                if (type === "path") {
                    pageStack.push("ObjectPage.qml",
                        {"service": service, "sessionBus": sessionBus,
                        "objectPath": path}
                    );
                }
            }
        }
    }
}

