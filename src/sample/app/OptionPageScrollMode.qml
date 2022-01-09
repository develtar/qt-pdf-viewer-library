import QtQuick 2.0

import "../components" as CustomComponents
import "../"

BaseOptionSection {
    title: "Scroll modes:"

    CustomComponents.Button{
        image.source: "qrc:/icons/view_horizontal_white_24dp.svg"

        onClicked: {
            pdfView.setScrollMode(pdfView._SCROLL_MODE_HORIZONTAL)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/view_vertical_white_24dp.svg"

        onClicked: {
            pdfView.setScrollMode(pdfView._SCROLL_MODE_VERTICAL)
        }
    }
    CustomComponents.Button{
        image.source: "qrc:/icons/view_wrapped_white_24dp.svg"

        onClicked: {
            pdfView.setScrollMode(pdfView._SCROLL_MODE_WRAPPED)
        }
    }
    CustomComponents.Button{
        image.source: hand? "qrc:/icons/touch_app_white_24dp.svg"
                          : "qrc:/icons/text_format_white_24dp.svg"

        property bool hand: pdfView.toolMode === pdfView._TOOL_MODE_HAND

        onClicked: {
            hand = !hand

            var mode = hand? pdfView._TOOL_MODE_HAND:pdfView._TOOL_MODE_CURSOR
            pdfView.setToolMode(mode)
        }
    }
}
