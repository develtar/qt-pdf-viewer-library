import QtQuick 2.0

Item {

    /*
        Emitted when the requested permission is granted
    */
    signal permissionGranted(var permission)


    /*
        Emitted when the requested permission is denied
    */
    signal permissionDenied(var permission)

    /*
        Returns true if the given permission is granted, false otherwise

        @param permission {string}: the permission name

        @return {boolean}
    */
    property var isPermissionGranted: function(permission){
        return true
    }

    /*
        Requests the given permissions to the current os.

        @note: By default permission is granted. This method
        must be overridden by children classes and request it
        according to the os.

        @param permission {array}: the list of permissions name
    */
    property var requestPermissions: function(permissions){
        for(var i=0; i<permissions.length; i++){
            var permission = permissions[i]

            if(permission!==""){
                console.debug("Requesting permission: ", permission)
            }

            permissionGranted(permission)
        }
    }

}
