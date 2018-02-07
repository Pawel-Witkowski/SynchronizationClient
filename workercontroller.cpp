#include "workercontroller.h"

WorkerController::WorkerController(QObject *parent) : QObject(parent)
{

}

void WorkerController::startConnection(QString ip, QString port)
{
    emit emitWorkerConnect(ip,port);
}

