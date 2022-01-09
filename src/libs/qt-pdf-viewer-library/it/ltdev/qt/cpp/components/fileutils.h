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
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QDir>
#include <QMap>
#include <QTextStream>
#include <QDebug>
#include <typeinfo>
#include <QJsonObject>
#include <QUrl>

namespace LTDev {

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = nullptr);

    static void write(const QString &fileContent, const QString &filePath);
    static QString read(QString filePath);
    static bool exists(const QString &path);
    static bool copyDirs(const QString &sourceFolder, const QString &destFolder);
    static bool removeDir(const QString &dirPath);
    static QString joinPaths(const QStringList &paths);
signals:

};
}

#endif // FILEUTILS_H
