#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QThread>
#include <QQmlContext>
#include <clientworker.h>
#include <workercontroller.h>
int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QThread *thread = new QThread();
    ClientWorker *clientWorker = new ClientWorker();
    WorkerController *workerController = new WorkerController();
    QObject::connect(workerController,SIGNAL(emitWorkerConnect(QString,QString)),clientWorker,SLOT(connectToServer(QString,QString)),Qt::BlockingQueuedConnection);
    clientWorker->moveToThread(thread);
    //QObject::connect(thread,SIGNAL(started()),clientWorker,SLOT(connect()));
    QObject::connect(clientWorker,SIGNAL(finished()),thread,SLOT(quit()));
    QObject::connect(clientWorker,SIGNAL(finished()),clientWorker,SLOT(deleteLater()));
    QObject::connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("workerController", workerController);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
