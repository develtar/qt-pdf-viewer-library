import QtQuick 2.14
import QtWebView 1.1
import QtWebSockets 1.1

import QtWebChannel 1.0
import it.ltdev.qt.cpp.components 1.0

Item {
    id: root
    width: parent.width
    height: 500

    signal loaded()

    property alias url: webView.url
    property alias webView: webView
    property alias webChannel: channel
    property alias webTransport: transport
    property alias webSocketServer: server

    property int pages: 0
    property int page: 1
    onPageChanged: {
        // Limit page so it doesn't go out of bounds (-> [1, pages])
        var p = Math.min(Math.max(1, page), pages)
        if(page!==p) page = p

         backend.pageChanged(p)
        // or
        // webView.runJavaScript("pageChanged(%1);".arg(page))
    }

    /*
        The list of base64 images representing each pdf page
    */
    property var thumbnails: []

    /*
        The scaling value for the pdf
    */
    property var scale: 1

    readonly property int _SCROLL_MODE_VERTICAL: 0
    readonly property int _SCROLL_MODE_HORIZONTAL: 1
    readonly property int _SCROLL_MODE_WRAPPED: 2
    property var scrollModes: [_SCROLL_MODE_VERTICAL, _SCROLL_MODE_HORIZONTAL, _SCROLL_MODE_WRAPPED]
    property int scrollMode: _SCROLL_MODE_VERTICAL
    onScrollModeChanged: {
        console.debug("onScrollModeChanged | scrollMode: ", scrollMode)

        // Check if current scale mode is provided by pdf.js library
        var validMode = scrollModes.indexOf(scrollMode)!==-1
        if(validMode){
            backend.scrollModeChanged(scrollMode)
            // or
            // webView.runJavaScript("setScrollMode(%1);".arg(scrollMode))
        } else {
            scrollMode = _SCROLL_MODE_VERTICAL
        }
    }


    readonly property string _SCALE_MODE_CUSTOM: "custom"
    readonly property string _SCALE_MODE_ACTUAL: "page-actual"
    readonly property string _SCALE_MODE_AUTO: "auto"
    readonly property string _SCALE_MODE_FIT_PAGE: "page-fit"
    readonly property string _SCALE_MODE_FIT_PAGE_WIDTH: "page-width"
    readonly property string _SCALE_MODE_FIT_PAGE_HEIGHT: "page-height"
    property var scaleModes: [
        _SCALE_MODE_ACTUAL,
        _SCALE_MODE_AUTO,
        _SCALE_MODE_FIT_PAGE,
        _SCALE_MODE_FIT_PAGE_WIDTH,
        _SCALE_MODE_FIT_PAGE_HEIGHT,
    ]
    property string scaleMode: _SCALE_MODE_ACTUAL

    onScaleModeChanged: {
        // Check if current scale mode is provided by pdf.js library
        var validMode = scaleModes.indexOf(scaleMode)!==-1

        if(validMode){
            backend.scaleModeChanged(scaleMode)
            // or
            // webView.runJavaScript("setScaleMode(\"%1\");".arg(scaleMode))
        } else {
            // Custom mode, it is set when applying a custom scale value
            // (eg. when view is zoomed in/out)
            scaleMode = _SCALE_MODE_CUSTOM
        }

        console.debug("onScaleModeChanged | scaleMode:", scaleMode)
    }

    /*
        The QtObject that will be exposed to the browser environment
    */
    QtObject {
        id: backend

        /*
            The ID under which this object will be known in the browser environment
        */
        WebChannel.id: "backend"

        /*
            The signal that will notify the browser environment that
            scroll mode has changed.

            @param mode {int}: the scroll mode
        */
        signal scrollModeChanged(var mode)

        /*
            The signal that will notify the browser environment that
            page has changed.

            @param page {int}: the page
        */
        signal pageChanged(var page)


        /*
            The signal that will notify the browser environment that
            scale mode has changed.

            @param scaleMode {string}: the scale mode
        */
        signal scaleModeChanged(var scaleMode)

        /*
            Sets the pages property of the pdf view and notifies
            that pdf has been entirely loaded.

            @note: It is called from the browser environment.

            @param scale {float}: the scale value
        */
        function pdfLoaded(pages){
            root.pages = pages
            root.loaded()
        }

        /*
            Sets the thumbnails array of the pdf view.

            @note: It is called from the browser environment.

            @param thumbnails {array}: the list of base64 images which represent each pdf page
        */
        function updateThumbnails(thumbnails){
            root.thumbnails = thumbnails
        }

        /*
            Sets the page property of the pdf view.

            @note: It is called from the browser environment.

            @param page {int}: the scale value
        */
        function updatePage(page){
            root.page = page
        }

        /*
            Sets the scale property of the pdf view.

            @note: It is called from the browser environment.

            @param scale {float}: the scale value
        */
        function updateScale(scale){
            root.scale = scale
        }

        /*
            Sets the scroll mode property of the pdf view.

            @note: It is called from the browser environment.

            @param scrollMode {string}: the scroll mode
        */
        function updateScrollMode(scrollMode){
            root.scrollMode = scrollMode
        }

    }


    WebView {
        id: webView

        anchors.fill: parent
    }

    /*
        The channel through which data is exchanged between qml and browser environment
    */
    WebChannel {
        id: channel
        registeredObjects: [backend]
    }

    /*
        The socket transport which allows the browser environment to communicate
        with the qml backend. Any change on browser side will notify qml.
    */
    WebSocketTransport {
        id: transport
    }

    /*
        The socket server which allows the communication between qml and browser envirnoment.
    */
    WebSocketServer {
        id: server
        listen: true
        port: 55222

        onClientConnected: {
            if(webSocket.status === WebSocket.Open) {
                channel.connectTo(transport)
                webSocket.onTextMessageReceived.connect(transport.textMessageReceive)
                transport.onMessageChanged.connect(webSocket.sendTextMessage)
            }
        }
    }

    /*
        Loads the pdf document as base64 string.

        @param base64 {string}: the base64 document to load
    */
    function loadDocument(base64){
        webView.runJavaScript("loadDocument(\"%1\")".arg(base64))
    }

    /*
        Rotates the pdf by the given angle.

        @param angle {float}: the rotation angle
    */
    function rotate(angle){
        webView.runJavaScript("rotate(%1)".arg(angle));
    }

    /*
        Zooms the pdf in
    */
    function zoomIn(){
        // Set custom scaling mode
        scaleMode = _SCALE_MODE_CUSTOM

        webView.runJavaScript("zoomIn();")
    }

    /*
        Zooms the pdf out
    */
    function zoomOut(){
        // Set custom scaling mode
        scaleMode = _SCALE_MODE_CUSTOM

        webView.runJavaScript("zoomOut();")
    }

    /*
        Searches in the pdf document for the given text.
        Finds the first occurence of the text found.

        @param query {string}: the query/text to search for
        @param phraseSearch {boolean}: true if entire phrase must be searched, false otherwise
        @param caseSensitive {boolean}: true if case sensitive must be enabled, false otherwise
        @param highlightAll {boolean}: true if matches found must be highlighted, false otherwise
        @param findPrevious {boolean}: true if previous matches must be considered, false otherwise
    */
    function searchText(query, phraseSearch, caseSensitive, highlightAll, findPrevious){
         webView.runJavaScript("searchText(\"%1\", %2, %3, %4, %5, \"%6\")"
                               .arg(query)
                               .arg(phraseSearch)
                               .arg(caseSensitive)
                               .arg(highlightAll)
                               .arg(findPrevious)
                               .arg("find"))

    }
    /*
        Searches in the pdf document for the given text.
        Finds the next occurence of the text found.

        @param query {string}: the query/text to search for
        @param phraseSearch {boolean}: true if entire phrase must be searched, false otherwise
        @param caseSensitive {boolean}: true if case sensitive must be enabled, false otherwise
        @param highlightAll {boolean}: true if matches found must be highlighted, false otherwise
        @param findPrevious {boolean}: true if previous matches must be considered, false otherwise
    */
    function searchTextOccurance(query, phraseSearch, caseSensitive, highlightAll, findPrevious){
         webView.runJavaScript("searchText(\"%1\", %2, %3, %4, %5, \"%6\")"
                               .arg(query)
                               .arg(phraseSearch)
                               .arg(caseSensitive)
                               .arg(highlightAll)
                               .arg(findPrevious)
                               .arg("findagain"))
    }
}
