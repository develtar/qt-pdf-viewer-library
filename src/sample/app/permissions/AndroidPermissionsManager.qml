import QtQuick 2.0
import QtAndroidTools 1.0

BasePermissionsManager {
    id: root

    // @Override
    requestPermissions: function(permissions){
        QtAndroidAppPermissions.requestPermissions(permissions)
    }

    // @Override
    isPermissionGranted: function(permission){
        return QtAndroidAppPermissions.isPermissionGranted(permission)
    }

    Connections {
        target: QtAndroidAppPermissions

        function onRequestPermissionsResults(results){
            for(var i = 0; i < results.length; i++){
                var permission = results[i]

                if(permission.granted){
                    permissionGranted(permission.name)

                } else {
                    permissionDenied(permission.name)
                }
            }
        }
    }
}
