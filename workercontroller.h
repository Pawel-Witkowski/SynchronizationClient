#ifndef WORKERCONTROLLER_H
#define WORKERCONTROLLER_H

#include <QObject>

class WorkerController : public QObject
{
    Q_OBJECT
public:
    explicit WorkerController(QObject *parent = nullptr);
    Q_INVOKABLE void startConnection(QString ip, QString port);
signals:
    void emitWorkerConnect(QString, QString);

public slots:
};

#endif // WORKERCONTROLLER_H
