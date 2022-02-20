import QtQuick 2.0
import QtQuick.Controls 2.0

import "sample"
import "sample/app/permissions"

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 700
    height: 900
    title: qsTr("Qt PDF Viewer")

    /*
        Read external storage permission by os
    */
    property string permission_read_external_storage: {
        if(Qt.platform.os === "android"){
            return "android.permission.READ_EXTERNAL_STORAGE"
        }
        return ""
    }

    /*
        Write external storage permission by os
    */
    property string permission_write_external_storage: {
        if(Qt.platform.os === "android"){
            return "android.permission.WRITE_EXTERNAL_STORAGE"
        }
        return ""
    }

    /*
        Inits the permissions manager

        @param item {object}: the manager to init
    */
    function initPermissionsManager(item){
        if(item){
            var permissionManager = item

            // Connect permissions results signals
            permissionManager.permissionGranted.connect(function(permission){
                if(permission.length>0){
                    console.debug("Permission granted:", permission)
                }

                if((permission===permission_read_external_storage && permissionManager.isPermissionGranted(permission_write_external_storage))
                        || (permission===permission_write_external_storage && permissionManager.isPermissionGranted(permission_read_external_storage))){
                    firstPageLoader.sourceComponent = componentPdfPage
                }
            })
            permissionManager.permissionDenied.connect(function(permission){
                if(permission.length>0){
                    console.debug("Permission denied:", permission)
                }

                if(permission===permission_read_external_storage || permission===permission_write_external_storage){
                    Qt.quit()
                }
            })

            // Request permissions
            permissionManager.requestPermissions([permission_read_external_storage, permission_write_external_storage])
        }
    }

    /*
        The loader that will load the permissions manager by os
    */
    Loader {
        id: loaderPermissionsManager

        onItemChanged: {
            console.debug("Permission manager:", item)
            initPermissionsManager(item)
        }


        source: {
            if(Qt.platform.os === "android"){
                return "qrc:/sample/app/permissions/AndroidPermissionsManager.qml"
            }

            return "qrc:/sample/app/permissions/BasePermissionsManager.qml"
        }
    }


    /*
        The loader that will load first page on permission granted
    */
    Loader {
        id: firstPageLoader
        anchors.fill: parent
    }


    /*
        The page that should be loaded on permission granted
    */
    Component {
        id: componentPdfPage

        PdfPage {
            anchors.fill: parent
        }
    }


}
