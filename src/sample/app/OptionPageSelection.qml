import QtQuick 2.0

import "../components" as CustomComponents
import "../"

BaseOptionSection {
    title: "Page selection:"

    CustomComponents.Button{
        image.source: "qrc:/icons/arrow_downward_white_24dp.svg"

        onClicked: {
            pdfView.previousPage()
        }
    }

    Row {
        spacing: 0
        CustomComponents.TextField {
            width: 52
            enabled: false
            textInput {
                horizontalAlignment: Text.AlignRight
                validator: IntValidator{bottom: 1}
                text: String(pdfView.page)
            }
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            text: " of "+String(pdfView.pages)
            color: "white"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
        }
    }

    CustomComponents.Button{
        image.source: "qrc:/icons/arrow_upward_white_24dp.svg"

        onClicked: {
            pdfView.nextPage()
        }
    }


}
