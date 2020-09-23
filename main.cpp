#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "todolist.h"
#include "todomodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // This template function registers the C++ type in the QML system with the name qmlName, in the library imported from uri having the version number composed from versionMajor and versionMinor.
    qmlRegisterType<ToDoModel>("ToDo",1,0,"ToDoModel");
    // While the type has a name and a type, it cannot be created, and the given error message will result if creation is attempted.
    // This is useful where the type is only intended for providing attached properties or enum values.
    qmlRegisterUncreatableType<ToDoList>("ToDo",1,0,"ToDoList",QStringLiteral("ToDoList should not be cretaed in QML"));

    ToDoList toDoList;

    QQmlApplicationEngine engine;
    // Set the value of the name property on this context.
    engine.rootContext()->setContextProperty(QStringLiteral("toDoList"),&toDoList);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
