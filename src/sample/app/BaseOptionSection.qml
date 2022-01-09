import QtQuick 2.0

import "../components" as CustomComponents
import "../"

import it.ltdev.qt.qml.components 1.0 as LTDev

Column {
    id: root
    property LTDev.PdfView pdfView

    default property alias flowContent: flow.data

    property alias title: title.text

    spacing: 4

    Text {
        id: title
        color: "white"
        font.pixelSize: 16
    }


    property int maxWidth: 1000

    Flow {
        id: flow
        width: Math.min(root.maxWidth, flow.calculateChildrenWidth())
        spacing: 8

        /*
            Returns the total width of the children

            @return {int}
        */
        function calculateChildrenWidth(){
            var totWidth = 0
            for(var i=0; i<flow.children.length; i++){
                var child = flow.children[i]
                totWidth+=child.width+flow.spacing
            }
            return totWidth-spacing
        }


    }

}
