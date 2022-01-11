#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QFontDatabase>

#include "it/ltdev/qt/cpp/components/qtpdfviewerinitializer.h"
#include "sampleutils.h"

#ifdef __ANDROID__
#include "QtAndroidTools.h"
#endif

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

#ifdef __ANDROID__
    // Initialize Qt android tools library
    QtAndroidTools::initializeQmlTools();
#endif


    // Initialize QtPdfViewer library
    // To make the pdf module to function correctly across all platforms,
    // it is necessary to call QtPdfViewerInitializer::initialize() before in Qt>= 5.15.0, or after in Qt<5.15.0, creating
    // the QGuiApplication instance
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
    LTDev::QtPdfViewerInitializer::initialize();
    QGuiApplication app(argc, argv);
#else
    QGuiApplication app(argc, argv);
    LTDev::QtPdfViewerInitializer::initialize();
#endif



    // Delete QtPdfViewerInitializer instance on app close
    QObject::connect(&app, &QGuiApplication::aboutToQuit, LTDev::QtPdfViewerInitializer::getInstance(), LTDev::QtPdfViewerInitializer::deleteInstance);


    QQmlApplicationEngine engine;

    // Needed to import the custom module
    engine.addImportPath("qrc:/");
    engine.addImportPath(":/");

    // Install custom font
    qint32 fontId = QFontDatabase::addApplicationFont(":/fonts/PathwayGothicOne-Regular.ttf");
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);
    QFont font(fontList.first());
    QGuiApplication::setFont(font);


    SampleUtils *utils = new SampleUtils(&app);
    engine.rootContext()->setContextProperty("SampleUtils", utils);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
