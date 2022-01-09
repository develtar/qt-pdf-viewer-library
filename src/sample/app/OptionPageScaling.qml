import QtQuick 2.0

import "../components" as CustomComponents
import "../"

BaseOptionSection {
    title: "Scaling options:"

    CustomComponents.Button {
        id: btnZoomOut
        image.source: "qrc:/icons/remove_white_24dp.svg"

        onClicked: {
            pdfView.zoomOut()
        }
    }

    Rectangle {
        color: "#4d4d4d"
        height: btnZoomOut.height
        width: 72
        radius: 8

        Text {
            id: scaling
            color: "white"
            font.pixelSize: 14
            anchors.fill: parent

            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            text: String(parseFloat((pdfView.scale*100).toFixed(2)))+"%"
        }
    }


    CustomComponents.Button{
        image.source: "qrc:/icons/add_white_24dp.svg"

        onClicked: {
            pdfView.zoomIn()
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/crop_free_white_24dp.svg"

        onClicked: {
            pdfView.setScaleMode(pdfView._SCALE_MODE_AUTO)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/aspect_ratio_white_24dp.svg"

        onClicked: {
            pdfView.setScaleMode(pdfView._SCALE_MODE_FIT_PAGE)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/expand_vertical_white_24dp.svg"

        onClicked: {
            pdfView.setScaleMode(pdfView._SCALE_MODE_FIT_PAGE_HEIGHT)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/expand_horizontal_white_24dp.svg"

        onClicked: {
            pdfView.setScaleMode(pdfView._SCALE_MODE_FIT_PAGE_WIDTH)
        }
    }



}
