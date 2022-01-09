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
        stream << fileContent << Qt::endl;
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
