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
#ifndef QTPDFVIEWERINITIALIZER_H
#define QTPDFVIEWERINITIALIZER_H

#include <QObject>
#include <QtWebView/QtWebView>
#include <QQmlApplicationEngine>

#include "fileutils.h"
#include "WebSocketTransport.h"
#include "singleton.cpp"

#define PDF_VIEWER_VERSION "1.0.000"

namespace LTDev {

namespace DIR {
    static const QString &path="libs/pdfjs/";
}

class QtPdfViewerInitializer : public QObject, public Singleton<QtPdfViewerInitializer>
{
    Q_OBJECT

    Q_PROPERTY(QString viewer READ viewer NOTIFY viewerChanged)

    friend class Singleton;

public:
    /**
     * @brief Initializes the library
     */
    static void initialize();

    /**
     * @brief Initializes the viewer creating the folders needed for the pdf view.
     * Returns true if created or already initialized, false otherwise.
     */
    Q_INVOKABLE bool initializeViewer(bool force=false);

    /**
    * @brief Returns the base64 string of the given pdf file.
    **/
    Q_INVOKABLE static QByteArray pdfToBase64(const QString &path);

    Q_INVOKABLE QString root(){ return this->_root;}
    QString viewer(){ return this->_viewer;}

    Q_INVOKABLE bool initialized(){ return this->_initialized;}

    /**
    * @brief Returns the qml instance.
    **/
    static QObject *getQmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

protected:
    /**
     * @brief the directory in which the library is exported
     */
    QString _root;

    /**
     * @brief the path of the html viewer
     */
    QString _viewer;

    /**
     * @brief flag to know if library has been already exported
     */
    bool _initialized;


    /**
     * @brief Constructor
     */
    QtPdfViewerInitializer();

signals:
    void viewerChanged();

};

}
#endif // QTPDFVIEWERINITIALIZER_H
