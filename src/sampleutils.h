#ifndef SAMPLEUTILS_H
#define SAMPLEUTILS_H

#include <QObject>
#include <QStandardPaths>
#include <QFile>
#include "it/ltdev/qt/cpp/components/fileutils.h"


class SampleUtils : public QObject
{
    Q_OBJECT
public:
    explicit SampleUtils(QObject *parent = nullptr);

    /**
     * @brief Copies the pdf sample of the qrc in the download folder.
     * Returns the path of the pdf.
     */
    Q_INVOKABLE static QString copyPdfSampleInDownloadFolder();

    /**
     * @brief Returns true if the pdf exists, false otherwise
     */
    Q_INVOKABLE static bool pdfExists(const QString &path);
signals:

};

#endif // SAMPLEUTILS_H
