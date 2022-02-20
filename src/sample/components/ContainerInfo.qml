import QtQuick 2.0

Rectangle {
    id: root
    color: "#FFDEDE"
    border.color: "#BE0000"
    border.width: 2
    radius: 8

    property alias textView: textView
    property int padding: 4

    Text {
        id: textView
        width: parent.width-padding*2
        height: parent.height-padding*2
        anchors.centerIn: parent
        color: root.border.color

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        fontSizeMode: Text.Fit
        minimumPixelSize: 12
        font.pixelSize: 16
        wrapMode: Text.WordWrap
        clip: true
    }
}
