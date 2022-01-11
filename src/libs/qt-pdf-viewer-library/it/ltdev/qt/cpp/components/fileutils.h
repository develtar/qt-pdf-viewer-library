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

    /**
    * @brief Writes the passed content in the provided path.
    **/
    static void write(const QString &fileContent, const QString &filePath);

    /**
    * @brief Returns the content of the file passed
    **/
    static QString read(QString filePath);


    /**
    * @brief Returns true if the (file or dir) path exists, false otherwise
    **/
    static bool exists(const QString &path);

    /**
     * @brief Copies the source folder in the destination folder.
     */
    static bool copyDirs(const QString &sourceFolder, const QString &destFolder);

    /**
    * @brief Removes a directory recursively.
    **/
    static bool removeDir(const QString &dirPath);

    /**
    * @brief Concatenates the given paths.
    **/
    static QString joinPaths(const QStringList &paths);
signals:

};
}

#endif // FILEUTILS_H
