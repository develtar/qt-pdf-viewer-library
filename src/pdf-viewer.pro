QT += quick svg

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        sampleutils.cpp

RESOURCES += qml.qrc \
    icons.qrc \
    fonts.qrc

# Pdf View library
QML_IMPORT_PATH += $$PWD/
QML_IMPORT_PATH += $$PWD/libs/qt-pdf-viewer-library/
QML_DESIGNER_IMPORT_PATH += $$PWD/
QML_DESIGNER_IMPORT_PATH += $$PWD/libs/qt-pdf-viewer-library/
include($$PWD/libs/qt-pdf-viewer-library/qtpdfviewer.pri)



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


android {
# Android permissions tools library
# @see: https://github.com/FalsinSoft/QtAndroidTools/tree/1.5.5
QML_IMPORT_PATH += $$PWD/libs/android/QtAndroidTools-1.5.5/QtAndroidTools
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
DEFINES += \
    QTAT_APP_PERMISSIONS

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

include($$PWD/libs/android/QtAndroidTools-1.5.5/QtAndroidTools/QtAndroidTools.pri)
}

HEADERS += \
    sampleutils.h
