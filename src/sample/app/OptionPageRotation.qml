import QtQuick 2.0

import "../components" as CustomComponents
import "../"

BaseOptionSection {
    title: "Page rotation:"

    CustomComponents.Button{
        image.source: "qrc:/icons/rotate_left_white_24dp.svg"

        onClicked: {
            pdfView.rotate(-90)
        }
    }

    CustomComponents.Button{
        image.source: "qrc:/icons/rotate_right_white_24dp.svg"

        onClicked: {
            pdfView.rotate(90)
        }
    }
}
