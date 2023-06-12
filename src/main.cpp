#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QQuickWindow>
#include <QProcess>
#include "AppInfo.h"
#include "./include/base.h"
#include "./lang/Zh.h"

int main(int argc, char *argv[])
{
    //将样式设置为Basic，不然会导致组件显示异常
    qputenv("QT_QUICK_CONTROLS_STYLE","Basic");
    QGuiApplication::setOrganizationName("LWL");
    QGuiApplication::setOrganizationDomain("https://github.com/welkin-sky/Cloudrary");
    QGuiApplication::setApplicationName("Cloudary");
    QGuiApplication app(argc, argv);
    AppInfo* appInfo = new AppInfo();
    IPC ipc(0);
    if(!appInfo->isOwnerProcess(&ipc)){
        return 0;
    }
    app.setQuitOnLastWindowClosed(false);
    QQmlApplicationEngine engine;
    // 初始化上下文对象
    Zh zh;
    Base base;
    engine.rootContext()->setContextProperty("lang", &zh);
    engine.rootContext()->setContextProperty("base", &base);
    const QUrl url(QStringLiteral("qrc:/QML/App.qml"));
    //    const QUrl url(QStringLiteral("qrc:/example/qml/TestWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
