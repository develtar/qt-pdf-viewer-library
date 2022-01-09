import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    id: root

    property int padding: 8
    property alias textInput: textInput

    implicitHeight: 56
    implicitWidth: 92
    color: "#4d4d4d"
    radius: 8

    TextInput {
        id: textInput
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        width: parent.width-padding*2
        height: parent.height-padding*2
        anchors.centerIn: parent
        font.pixelSize: 18
        color: "white"
    }
}
