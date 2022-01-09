import QtQuick 2.0
import "../components" as CustomComponents
import "../app"
import "../"

import it.ltdev.qt.qml.components 1.0 as LTDev

Column {
    property LTDev.PdfView pdfView

    spacing: 16

    Text {
        text: "Preview:"
        color: "white"
        font.pixelSize: 16
    }


    ListView {
        id: listViewThumbnails

        width: parent.width-24
        height: 176
        currentIndex: pdfView.page

        interactive: contentWidth>width
        clip: true
        model: pdfView.thumbnails

        orientation: ListView.Horizontal
        delegate: Item {
            width: thumbnail.width+24
            height: listViewThumbnails.height

            CustomComponents.Button{
                id: thumbnail

                width: image.width
                height: parent.height-24

                padding: 0
                image {
                    width: undefined
                    fillMode: Image.PreserveAspectFit
                    source: modelData
                }

                onClicked: {
                    pdfView.setPage(index+1)
                }

                /*
                        Selection indicator
                    */
                Rectangle {
                    id: selectionIndicator
                    visible: pdfView.page===(index+1)
                    color: "black"
                    opacity: 0.3
                    anchors.fill: parent
                }

                /*
                        Selection indicator border
                    */
                Rectangle {
                    visible: selectionIndicator.visible
                    anchors.fill: parent
                    color: "transparent"
                    border.width: 3
                    border.color: "#0066cc"
                }
            }

        }
    }

}
