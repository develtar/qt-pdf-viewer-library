#include "sampleutils.h"

SampleUtils::SampleUtils(QObject *parent) : QObject(parent)
{

}

/**
 * Copies the pdf sample of the qrc in the download folder.
 * Returns the path of the pdf.
 *
 * @return QString
 */
QString SampleUtils::copyPdfSampleInDownloadFolder()
{
    // Copy the pdf sample from qrc to the download folder of the device
    QString downloadDir = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString pdfPath = downloadDir+ "/sample.pdf";
    QFile::remove(pdfPath);
    QFile::copy(":/sample.pdf", pdfPath);
    return pdfPath;
}

/**
 * Returns true if the pdf exists, false otherwise
 *
 * @param path: the pdf path to check
 *
 * @return bool
 */
bool SampleUtils::pdfExists(const QString &path){
    return LTDev::FileUtils::exists(path);
}
