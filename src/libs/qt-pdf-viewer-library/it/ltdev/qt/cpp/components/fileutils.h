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
