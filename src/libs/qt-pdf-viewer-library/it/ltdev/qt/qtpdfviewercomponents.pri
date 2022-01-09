QT += webchannel websockets webview

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

RESOURCES += \
    $$PWD/qml/components/qtpdfviewercomponents.qrc

HEADERS += \
    $$PWD/cpp/components/WebSocketTransport.h \
    $$PWD/cpp/components/fileutils.h \
    $$PWD/cpp/components/qtpdfviewerinitializer.h \
    $$PWD/cpp/components/singleton.h

SOURCES += \
    $$PWD/cpp/components/fileutils.cpp \
    $$PWD/cpp/components/qtpdfviewerinitializer.cpp \
    $$PWD/cpp/components/singleton.cpp

