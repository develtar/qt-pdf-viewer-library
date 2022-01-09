/*
 *
 *  MIT License
 *
 *  Copyright (c) 2022 Leonardo Tarollo (LTDev) <develtar@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include "qtpdfviewerinitializer.h"

namespace LTDev {

/**
 * Initializes the library
 */
void QtPdfViewerInitializer::initialize()
{
    // To make the Qt WebView module function correctly across all platforms,
    // it is necessary to call QtWebView::initialize() before creating
    // the QGuiApplication instance.
    QtWebView::initialize();

    // Expose classes to qml
    qmlRegisterType<LTDev::WebSocketTransport>("it.ltdev.qt.cpp.components", 1, 0, "WebSocketTransport");
    qmlRegisterSingletonType<QtPdfViewerInitializer>("it.ltdev.qt.cpp.components", 1, 0, "QtPdfViewerInitializer", &QtPdfViewerInitializer::getQmlInstance);
}

/**
 * Initializes the viewer creating the folders needed for the pdf view.
 * Returns true if created or already initialized, false otherwise.
 *
 * @return bool
 */
bool QtPdfViewerInitializer::initializeViewer(bool force){
    if(!this->_initialized || force){
        FileUtils::removeDir(this->_root);

        // Copy pdf js folder in the application path (it depends on platform)
        // @note: the copy of the folder is necessary for Android devices
        // because webview cannot access files from qrc directly, so
        // we create a local folder from which files will be loaded.
        bool copied = FileUtils::copyDirs(":/pdfjs", this->_root);
        bool notify = _initialized != copied;
        if(notify){
            _initialized = copied;
            if(_initialized) {
                // Notify viewer
                emit viewerChanged();
            }
        }
    }

    return this->_initialized;
}

/**
*
* Returns the base64 string of the given pdf file.
*
* @param path: the pdf file
*
* @return QByteArray
*
**/
QByteArray QtPdfViewerInitializer::pdfToBase64(const QString &path)
{
    if(FileUtils::exists(path)){
        QFile input(path);
        if (input.open(QIODevice::ReadOnly)) {
            QByteArray base64 = input.readAll().toBase64();
            return base64;
        }
    }

    return QByteArray();
}

/**
* Returns the qml instance.
**/
QObject *QtPdfViewerInitializer::getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    return QtPdfViewerInitializer::getInstance();
}

/**
 * @brief Constructor
 */
QtPdfViewerInitializer::QtPdfViewerInitializer()
{
    QString appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString dir = FileUtils::joinPaths(QStringList() << appDir << DIR::path);

    this->_root = dir;
    this->_viewer = FileUtils::joinPaths(QStringList() << dir << "viewer.html");

    this->_initialized = false;
}


}
