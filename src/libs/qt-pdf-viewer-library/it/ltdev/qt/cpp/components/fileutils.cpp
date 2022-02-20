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
#include "fileutils.h"

namespace LTDev {

FileUtils::FileUtils(QObject *parent) : QObject(parent)
{

}


/**
*
* Writes the passed content in the provided path.
*
* @param fileContent: the string to insert into the file
* @param filePath: the path of the file in which to write the content
*
**/
void FileUtils::write(const QString &fileContent, const QString &filePath){
    QFile file(filePath);

    // Write into file
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text)) {
        QTextStream stream( &file );

#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
        stream << fileContent << Qt::endl;
#else
        stream << fileContent << endl;
#endif

        file.close();
    }
}


/**
*
* Returns the content of the file passed
*
* @param filePath: the path of the file to read
*
* @return QString
*
**/
QString FileUtils::read(QString filePath)
{
    QString lines="";
    if(exists(filePath)){

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            while (!stream.atEnd())
            {
                lines.append(stream.readLine());
            }
        }
        file.close();
    }

    return lines;
}



/**
*
* Returns true if the (file or dir) path exists, false otherwise
*
* @param path: the path to check
*
* @return bool
*
**/
bool FileUtils::exists(const QString &path)
{
    if(path.isNull() || path.isEmpty())
        return false;

    // Checks the existance of path and "file://"+path
    return  QFile::exists(path) || QFileInfo::exists(QUrl(path).toString()) || QFileInfo::exists(QUrl(path).toLocalFile());
}

/**
 * Copies the source folder in the destination folder.
 *
 * @param sourceFolder: the folder to copy
 * @param destFolder: the destination folder
 *
 * @return bool
 */
bool FileUtils::copyDirs(const QString &sourceFolder, const QString &destFolder)
{
    // Check if source folder exists
    QDir sourceDir(sourceFolder);
    if(!exists(sourceFolder))
        return false;

    // Create destination dir if it doesn't exist
    QDir destDir(destFolder);
    if(!destDir.exists()){
        QDir().mkpath(destFolder);
    }

    // Copy all files
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++){
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        QFile::copy(srcName, destName);
    }

    // Copy all sub folders recursively
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++){
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        copyDirs(srcName, destName);
    }

    return true;
}



/**
*
* Removes a directory recursively.
*
* @param dirPath: the path of the directory to delete
*
* @warning pay attention using this method as root
*
* @return bool
*
**/
bool FileUtils::removeDir(const QString &dirPath){
    if(dirPath.compare("")==0) return false;

    if(QFile(dirPath).exists()) return QDir(dirPath).removeRecursively();
    return false;
}


/**
*
* Concatenates the given paths.
*
* @param paths: the list of paths to concatenate
*
* @return QString
*
**/
QString FileUtils::joinPaths(const QStringList &paths)
{
    QString fullPath = "";

    for(QString path: paths){
        fullPath = QDir(fullPath).filePath(path);
    }

    return fullPath;
}

}
