#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QQmlContext>
#include <QFontDatabase>

#include "it/ltdev/qt/cpp/components/qtpdfviewerinitializer.h"
#include "sampleutils.h"

#ifdef __ANDROID__
#include "QtAndroidTools.h"
#endif

void run() {
     // Example code to create WebView using C++ method.
     // However, it is not recommended to construct
     // everything using C++. It is very troublesome.
     // It just show how can you execute code with
     // Android application UI thread
     QAndroidJniEnvironment env;

     QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
                                                                            "activity", "()Landroid/app/Activity;");
     QAndroidJniObject webView("android/webkit/WebView",
                               "(Landroid/content/Context;)V",
                                activity.object<jobject>());

     QAndroidJniObject frameLayout = activity.callObjectMethod("findViewById","(I)Landroid/view/View;",
                                                               0x01020002); // Hard coded value of android.R.id.content
     QAndroidJniObject layout("android/widget/RelativeLayout",
                               "(Landroid/content/Context;)V",
                                activity.object<jobject>());

     QAndroidJniObject params = QAndroidJniObject("android/view/ViewGroup$LayoutParams",
                                 "(II)V",
                                 (int) 0xffffffff,
                                 (int) 0xffffffff);

     layout.callMethod<void>("addView",
                             "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                             webView.object<jobject>(),
                             params.object<jobject>());

     frameLayout.callMethod<void>("addView",
                                  "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                                  layout.object<jobject>(),
                                  params.object<jobject>());

     QAndroidJniObject url = QAndroidJniObject::fromString("http://qt-project.org");

     webView.callMethod<void>("loadUrl","(Ljava/lang/String;)V",url.object<jstring>());

     if (env->ExceptionOccurred()) {
         env->ExceptionDescribe();
         env->ExceptionClear();
     }

 }

void run2() {
/// https://github.com/benlau/qtandroidexamplecode/blob/master/qtandroidrunner/main.cpp
//    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
//                                                                           "activity", "()Landroid/app/Activity;");

    QAndroidJniObject webSettings;
    QtAndroid::runOnAndroidThreadSync([&webSettings](){
        // create our Java control on Android UI thread.
        webSettings = QAndroidJniObject("android.webkit.WebSettings",
                                                    "(Landroid/content/Context;)V",
                                                    QtAndroid::androidActivity().object<jobject>());
//        webSettings.callMethod<void>("setAllowFileAccess", "true");

        bool access = webSettings.callMethod<jboolean>("getAllowFileAccess");
        qDebug() << "webSettings:" <<webSettings.toString() << access;
    });


    return;
    // Example code to create WebView using C++ method.
    // However, it is not recommended to construct
    // everything using C++. It is very troublesome.
    // It just show how can you execute code with
    // Android application UI thread
    QAndroidJniEnvironment env;

    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative",
                                                                           "activity", "()Landroid/app/Activity;");
    QAndroidJniObject webView("android/webkit/WebView",
                              "(Landroid/content/Context;)V",
                               activity.object<jobject>());

    QAndroidJniObject frameLayout = activity.callObjectMethod("findViewById","(I)Landroid/view/View;",
                                                              0x01020002); // Hard coded value of android.R.id.content
    QAndroidJniObject layout("android/widget/RelativeLayout",
                              "(Landroid/content/Context;)V",
                               activity.object<jobject>());

    QAndroidJniObject params = QAndroidJniObject("android/view/ViewGroup$LayoutParams",
                                "(II)V",
                                (int) 0xffffffff,
                                (int) 0xffffffff);

    layout.callMethod<void>("addView",
                            "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                            webView.object<jobject>(),
                            params.object<jobject>());

    frameLayout.callMethod<void>("addView",
                                 "(Landroid/view/View;Landroid/view/ViewGroup$LayoutParams;)V",
                                 layout.object<jobject>(),
                                 params.object<jobject>());

    QAndroidJniObject url = QAndroidJniObject::fromString("http://qt-project.org");

    webView.callMethod<void>("loadUrl","(Ljava/lang/String;)V",url.object<jstring>());

    if (env->ExceptionOccurred()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
    }

}
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

#ifdef __ANDROID__
    // Initialize Qt android tools library
    QtAndroidTools::initializeQmlTools();
#endif
//    run2();

//- https://github.com/2gis/2gisqt5android/blob/master/qtandroidextras/src/androidextras/jni/qandroidjniobject.cpp
//- https://stuff.mit.edu/afs/athena/software/texmaker_v5.0.2/qt57/doc/qtandroidextras/qtandroid.html
//- https://stackoverflow.com/questions/75940926/opening-the-android-settings-through-qandroidjniobject
//- https://docplayer.net/36769499-Practical-qt-on-android-jni.html
//- https://stackoverflow.com/questions/27092044/android-art-runtime-check-jni-cc-error-on-package-name
//- https://doc.qt.io/qt-6/qjniobject.html
//    QAndroidJniObject webSettings("android/webkit/WebSettings",
//                                  "(Landroid/app/Activity;)V",
//                                  QtAndroid::androidActivity().object<jobject>());
    QAndroidJniEnvironment environment;
    jobject clazz =  environment.findClass("android/webkit/WebSettings");
    QAndroidJniObject webSettings(clazz);

    jclass objectClass = environment->GetObjectClass(webSettings.object<jobject>());
//    environment->RegisterNatives(objectClass, jniMethod, sizeof(jniMethod)/sizeof(JNINativeMethod));
//    environment->DeleteLocalRef(objectClass);

    //    QtAndroid::runOnAndroidThreadSync([&webSettings](){
    //        // create our Java control on Android UI thread.
    //        webSettings = QAndroidJniObject("android.webkit.WebSettings",
    //                                                    "(Landroid/content/Context;)V",
    //                                                    QtAndroid::androidActivity().object<jobject>());
    //        webSettings.callMethod<void>("setAllowFileAccess", "true");
    //    });

    qDebug() << "webSettings.isValid():" << webSettings.isValid();
    if(webSettings.isValid()){
    //    webSettings.callMethod<void>("setAllowFileAccess",  "(Z)V", true);
        bool allow = webSettings.callMethod<jboolean>("getAllowFileAccess");
        qDebug() << "webSettings | Access:" << webSettings.toString() << allow;
    }

    QAndroidJniEnvironment env;
    jobject cls =  env.findClass("android/webkit/WebSettings");


    QAndroidJniObject p(cls);
    bool access = p.callMethod<jboolean>("getAllowFileAccess");
    qDebug() << "Access:" << p.toString() << access;
if(p.isValid()){
    p.callMethod<void>("setAllowFileAccess",  "(Z)V", true);
}

//    access = p.callMethod<jboolean>("getAllowFileAccess");
//    qDebug() << "Access:" << p.toString() << access;

    // Continue the execution normally
    qDebug() << "cls: " << cls << p.toString() << p.isValid() << access;


//    QtAndroid::runOnAndroidThreadSync([&webSettings](){
//        // create our Java control on Android UI thread.
//        webSettings = QAndroidJniObject("android.webkit.WebSettings",
//                                                    "(Landroid/content/Context;)V",
//                                                    QtAndroid::androidActivity().object<jobject>());
//        webSettings.callMethod<void>("setAllowFileAccess", "true");
//    });


//    // Continue the execution normally
//    qDebug() << "webSettings: " << webSettings.toString() << webSettings.isValid();

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
