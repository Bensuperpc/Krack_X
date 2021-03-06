//#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QQuickStyle>
#include <QStringList>

#include "applicationui.h"

#include "about_compilation.h"


int main(int argc, char *argv[])
{
    Applicationui appui;

    about_compilation ac;

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //for theme
    //qputenv("QT_QUICK_CONTROLS_STYLE", "material");
    QQuickStyle::setStyle("Material");

    //If you use QML app (without QtWidgets)
    //QGuiApplication app(argc, argv);

    //If you use QML and QtWidgets app(Graphics)
    QApplication app(argc, argv);
    //QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    //QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);

    QQmlApplicationEngine engine;



    //For combobox
    QStringList tmp;
    tmp << "1" << "2" << "3" << "4" << "5" << "6" << "7";
    appui.setComboList(tmp);


    //Add C++ instance in QML engine
    QQmlContext* context = engine.rootContext();
    context->setContextProperty("myApp", &appui);


    // some more context properties
    //appui.addContextProperty(context);
    context->setContextProperty("myModel", QVariant::fromValue(appui.comboList()));
    //engine.rootContext()->setContextProperty("qtversion", QString(qVersion()));
    context->setContextProperty("qtversion", QString(qVersion()));
    context->setContextProperty("about_compilation", &ac);

    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
