import QtQuick 2.0

import "qrc:///qnxcarui/qml/common/util.js" as Util

Item {
    /**
     * The source URL of the artwork.
     */
    property string source;

    /**
     * The artwork image's QML Image.smooth property.
     */
    property alias smooth: artworkImage.smooth;

    /**
     * Flag indicating whether the assigned image source has been
     * loaded successfully.
     */
    property bool artworkLoaded: false;

    /**
     * Switches to the default album artwork image, then assigns the source
     * URL to the album artwork image. If/when the artwork image loads successfully,
     * the component will switch from the default to the loaded album artwork.
     */
    onSourceChanged: {
        // Reset the album artwork source URL, this will cause the image status to change
        // to Image.Null, causing the artworkLoaded flag to revert back to false, resulting
        // in the default album artwork being restored.
        artworkImage.source = "";

        // Attempt to load the new artwork source
        if(_util.fileExists(source)) {
            artworkImage.source = source;
        }
    }

    Image {
        id: defaultArtwork

        anchors.fill: parent
        visible: !artworkLoaded
        source: Util.fromTheme("MediaControl/album_def.png")
    }

    Rectangle {
        id: artworkContainer

        anchors.fill: parent
        visible: artworkLoaded
        color: "#000"

        Image {
            id: artworkImage

            anchors.fill: parent
            fillMode: Image.PreserveAspectFit

            onStatusChanged: {
                if(status === Image.Ready) {
                    artworkLoaded = true;
                } else {
                    artworkLoaded = false;
                }
            }

        }
    }
}
