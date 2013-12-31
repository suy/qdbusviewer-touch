import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    initialPage: ServicesPage { }

    cover: Component {
        CoverBackground {
            CoverPlaceholder { text: "D-Bus viewer" }
        }
    }
}


