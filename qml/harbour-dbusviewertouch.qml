import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    initialPage: ServicesPage { }

    signal backToStart()

    pageStack.onCurrentPageChanged: {
        console.log(pageStack.currentPage, pageStack.depth)
        if (pageStack.currentPage === initialPage) {
            console.log("At the start.");
            backToStart();
        }
    }

    cover: Component {
        CoverBackground {
            CoverPlaceholder { text: "D-Bus viewer" }
        }
    }
}


