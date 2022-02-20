/*
 *
 *  Copyright 2022 Leonardo Tarollo (LTDev) <develtar@gmail.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

// The QtObject from QML side
var backend;

window.onload = function()
{
    // @note: Since Android 9, socket connections using clear text communication are disabled by default,
    // (so, those type of connections are refused) emitting the following error:
    // "WebSocket connection to 'ws://127.0.0.1:55222/' failed: Error in connection
    // establishment: net::ERR_CONNECTION_REFUSED" (or net::ERR_CLEARTEXT_NOT_PERMITTED)
    //
    // To solve it, add in the application tag in the manifest this property -> android:usesCleartextTraffic="true"
    // @see: https://stackoverflow.com/questions/54752716/why-am-i-seeing-neterr-cleartext-not-permitted-errors-after-upgrading-to-cordo
    var socket = new WebSocket("ws://127.0.0.1:55222");

    // The JavaScript QWebChannel object should be constructed once the transport object
    // is fully operational. In case of a WebSocket, that means you should create the QWebChannel
    // in the socket's onopen handler.
    // @see: https://doc.qt.io/qt-5/qtwebchannel-javascript.html
    socket.onopen = function()
    {
        // @note: On older browsers (EcmaScript <6) lamdas and other methods are not defined, so this
        // could cause an error on finding QWebChannel. For this reason, qwebchannel.js has been
        // modified to support older versions of javascript, and it has been included
        // in the html file. This file cannot be included in the qrc, because on
        // Android devices QWebChannel is not found if included in the html file
        // with <script type="text/javascript" src="qrc:///qtwebchannel/qwebchannel.js"></script>.
        // For this reason, qtwebchannel.js must be included from a local path or inside this file.
        //
        // The original qwebchannel.js file (without modifications) can be retrieved here:
        // @see: https://github.com/qt/qtwebchannel/blob/5.15.2/examples/webchannel/shared/qwebchannel.js
        //
        var webChannel = new QWebChannel(socket, function(channel) {
            // Once the callback passed to the QWebChannel object is invoked, the channel has finished
            // initialization and all published objects are accessible to the HTML client via
            // the channel.objects property
            backend = channel.objects.backend;

            // Connect signals emitted by the pdf viewer
            connectPdfViewerSignals()
        });
    };

    socket.onerror = function(error) {
//        alert("web channel error: " + error);
    };
}

/*
    Connects the signals of the pdf viewer
*/
function connectPdfViewerSignals(){
    // Connect signals emitted by the pdf viewer
    PDFViewerApplication.pdfViewer.eventBus.on('pagerendered', function(evt){
        backend.pdfLoaded(PDFViewerApplication.pagesCount)

        // Extract pdf pages as base64 images
        extractThumbnails(0.3, function(thumbnails){
            backend.updateThumbnails(thumbnails)
        })
    });

    PDFViewerApplication.pdfViewer.eventBus.on('pagechanging', function(evt){
        backend.updatePage(evt.pageNumber)
    });

    PDFViewerApplication.pdfViewer.eventBus.on('scalechanging', function(evt){
        backend.updateScale(evt.scale)
    });

    PDFViewerApplication.pdfViewer.eventBus.on('scrollmodechanged', function(evt){
        backend.updateScrollMode(evt.mode)
    });

    PDFViewerApplication.pdfCursorTools.eventBus.on('switchcursortool', function(evt){
        backend.updateToolMode(evt.tool)
    });

    PDFViewerApplication.pdfViewer.eventBus.on('erroroccurred', function(evt){
        backend.error(evt.msg)
    });

    // Signal that html viewer page has been loaded
    backend.viewerLoaded()
}


/*
    Loads the pdf document as base64 string.

    @param base64 {string}: the base64 document to load
*/
function loadDocument(base64){
    // Delay load to allow the javascript
    // environment to be ready
    sleep(200).then(function() {
        var array = base64ToUint8Array(base64)

        // Load pdf document as an Uint8Array
        PDFViewerApplication.open(array);
    });
}

/*
    Sets the pdf viewer page to the given one.

    @param page {int}: the page to set
*/
function setPage(page){
    PDFViewerApplication.page=page;
}

/*
    Rotates the pdf by the given angle.

    @param angle {float}: the rotation angle
*/
function rotate(angle){
    PDFViewerApplication.rotatePages(angle);
}

/*
    Zooms the pdf in.
*/
function zoomIn(){
    PDFViewerApplication.zoomIn();
}

/*
    Zooms the pdf out.
*/
function zoomOut(){
    PDFViewerApplication.zoomOut();
}

/*
    Scales the pdf with the given mode.

    @param scaleMode {string}: the scaling mode to apply
*/
function setScaleMode(scaleMode){
    PDFViewerApplication.pdfViewer.currentScaleValue=scaleMode;
}

/*
    Sets the pdf viewer scroll mode with the given value.

    @param scrollMode {int}: the scroll mode to apply
*/
function setScrollMode(scrollMode){
     PDFViewerApplication.pdfViewer.setScrollMode(scrollMode);
}


/*
    Sets the pdf viewer tool mode with the given value.

    @param toolMode {int}: the toolMode mode to apply
*/
function setToolMode(toolMode){
    PDFViewerApplication.pdfCursorTools.switchTool(toolMode)
}


/*
    Searches in the pdf document for the given text.

    @param query {string}: the query/text to search for
    @param phraseSearch {boolean}: true if entire phrase must be searched, false otherwise
    @param caseSensitive {boolean}: true if case sensitive must be enabled, false otherwise
    @param highlightAll {boolean}: true if matches found must be highlighted, false otherwise
    @param findPrevious {boolean}: true if previous matches must be considered, false otherwise
*/
function searchText(query, phraseSearch, caseSensitive, highlightAll, findPrevious, command){
    if(query===undefined) query = ""
    if(phraseSearch===undefined) phraseSearch = true
    if(caseSensitive===undefined) caseSensitive = false
    if(highlightAll===undefined) highlightAll = true
    if(findPrevious===undefined) findPrevious = false
    if(command===undefined) command = "find"

    PDFViewerApplication.findController.executeCommand(
                command, {
                    query: query,
                    phraseSearch: phraseSearch,
                    caseSensitive: caseSensitive,
                    highlightAll: highlightAll,
                    findPrevious: findPrevious
                });

}


/*
    Extracts the pdf pages as base64 images.

    @param scale {float}: the scaling value
    @param callbackOnExtractionCompleted {function}: the callback called when extraction is completed
*/
function extractThumbnails(scale, callbackOnExtractionCompleted){
    var thumbnails = []
    var pagesCount = PDFViewerApplication.pagesCount;

    // Create an off-screen canvas that will be used to
    // create images of the pdf pages
    var canvas = document.createElement('canvas');
    var ctx = canvas.getContext('2d');

    // The recursive function that will extract pdf pages starting from page 1
    function extractThumbnail(pageIndex, scale, callback) {
        // Promise to retrieve first page
        PDFViewerApplication.pdfDocument.getPage(pageIndex).then(function(page) {
            var viewport = page.getViewport(scale);

            canvas.height = viewport.height;
            canvas.width = viewport.width;

            var renderContext = {
                canvasContext: ctx,
                viewport: viewport
            };

            // Render page in the created canvas context
            page.render(renderContext).then(function() {
                // Store compressed image data in a base64 string
                thumbnails.push(canvas.toDataURL());


                if (pageIndex < pagesCount) {
                    pageIndex++;

                    // Extract next page
                    extractThumbnail(pageIndex, scale, callback);
                } else {
                    // All pages has been extracted, call the callback function
                    callback(thumbnails);
                }
            });
        });
    }

    // Start page extraction from page 1
    if (pagesCount>=1) {
        extractThumbnail(1, scale, callbackOnExtractionCompleted);
    }
}


/*
    Converts the base64 string to a Uint8Array.

    @param base64 {string}: the base64 string

    @return {Uint8Array}
*/
function base64ToUint8Array(base64){
    var raw = atob(base64);
    var rawLength = raw.length;
    var array = new Uint8Array(new ArrayBuffer(rawLength));


    for(var i = 0; i < rawLength; i++) {
        array[i] = raw.charCodeAt(i);
    }

    return array
}

/*
    Creates a promise object that will be active
    after ms milliseconds.

    @param ms {int}: the milliseconds that the Promise will wait before starting its job

    @return {Promise}
*/
function sleep(ms){
    return new Promise(function(resolve) {
        setTimeout(resolve, ms)
    });
}





