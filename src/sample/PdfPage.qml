import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtWebView 1.1


import "components" as CustomComponents
import "app"
import "app/permissions"

import it.ltdev.qt.qml.components 1.0 as LTDev

Rectangle {
    id: root
    color: "#3e3f3f"

    property StackView view

    property int closedTopbarHeight: 86
    property int topbarHeight: {
        var h = closedTopbarHeight
        var optionsHeight = containerOptions.visible? divider.height+containerOptions.height:0
        var pagesPreviewHeight = containerPreviewPages.visible? divider2.height+containerPreviewPages.height:0

        return closedTopbarHeight+optionsHeight+pagesPreviewHeight
    }

    Column {
        anchors.fill: parent
        spacing: 0

        Item {
            id: topbar
            width: parent.width
            height: topbarHeight

            Behavior on height {
                SmoothedAnimation {id: animOpen; duration: 300; easing.type: Easing.InOutCubic}
            }

            Column {
                id: columnLayout
                width: parent.width-36
                height: parent.height-36
                anchors.centerIn: parent

                RowLayout {
                    id: header
                    spacing: 24
                    width: parent.width

                    Text {
                        text: "Qt PDF Viewer"
                        font.pixelSize: 30
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                        color: "white"
                    }

                    Row {
                        spacing: 6

                        CustomComponents.Button{
                            id: btnShowPreview
                            property bool previewEnabled: false
                            visible: pdfView.thumbnails.length>0

                            padding: 12
                            color: previewEnabled? "#4d4d4d":"transparent"
                            image.source: "qrc:/icons/table_chart_white_24dp.svg"

                            onClicked: {
                                previewEnabled=!previewEnabled
                            }
                        }

                        CustomComponents.Button{
                            id: btnOptions
                            property bool optionsEnabled: false

                            padding: 12
                            color: optionsEnabled? "#4d4d4d":"transparent"
                            image.source: "qrc:/icons/tune_white_24dp.svg"

                            onClicked: {
                                optionsEnabled=!optionsEnabled
                            }
                        }
                    }
                } // RowLayout


                Item {
                    id: divider
                    visible: containerOptions.visible
                    width: parent.width
                    height: 24
                }

                /*
                    PDF Options
                */
                Flow {
                    id: containerOptions
                    visible: btnOptions.optionsEnabled
                    spacing: 24

                    width: parent.width

                    OptionPageScrollMode {
                        pdfView: pdfView
                    }

                    OptionPageSelection {
                        pdfView: pdfView
                    }

                    OptionPageRotation {
                        pdfView: pdfView
                    }

                    OptionPageSearch {
                        pdfView: pdfView
                    }

                    OptionPageScaling {
                        pdfView: pdfView
                        maxWidth: parent.width
                    }
                }

                Item {
                    id: divider2
                    visible: containerPreviewPages.visible
                    width: parent.width
                    height: 24
                }

                /*
                    PDF pages preview
                */
                Item {
                    id: containerPreviewPages
                    visible: btnShowPreview.previewEnabled
                    width: parent.width
                    height: previewPages.height

                    PreviewPages {
                        id: previewPages
                        pdfView: pdfView

                        width: parent.width
                        anchors.centerIn: parent
                    }

                }
            }
        } // Top bar


        Rectangle {
            id: pdfContainer
            width: parent.width
            height: parent.height-closedTopbarHeight
            color: "lightgrey"

            LTDev.PdfView {
                id: pdfView
                anchors.fill: parent

                // Setting visibility/opacity to manage loading states (eg. showing an error message or a busy indicator):
                // - on Desktop: setting the opacity (only) should be sufficient to managing loading states
                // - on Android: must be set both opacity and visibility to managing loading states
                //
                visible: false
                opacity: 0

                onError: {
                    // Hide pdfview on error
                    pdfView.visible = false
                    pdfView.opacity = 0

                    console.error("Error: ", message)

                    // Parse json error message
                    var json = JSON.parse(message)

                    // Update container error text
                    containerError.textView.text = "Error: "+json.error.generic + " " + json.error.detailed
                }

                onViewerLoaded: {
                    // Copy pdf sample from qrc to download folder
                    var pdfPath = SampleUtils.copyPdfSampleInDownloadFolder()

                    if(SampleUtils.pdfExists(pdfPath)){
                        // To correctly load the pdf, pdfview must be visible
                        pdfView.visible = true

                        // Load pdf only when viewer is ready
                        pdfView.load(pdfPath)
                    } else {
                        console.warn("Pdf ", pdfPath, "not found")
                    }
                }

                onPdfLoaded: {
                    // Pdf has been correctly loaded, ensure pdf view visibility
                    pdfView.visible = true
                    pdfView.opacity = 1

                    // Update container error text (no error occurred)
                    containerError.textView.text = ""
                }
            }


            /*
                Error info
            */
            CustomComponents.ContainerInfo {
                id: containerError
                visible: !pdfView.visible && textView.text.length>0

                width: Math.min(parent.width/2, 400)
                height: 65
                anchors.centerIn: parent
            }
        }

    }




}
