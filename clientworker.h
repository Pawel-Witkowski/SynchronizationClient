#ifndef CLIENTWORKER_H
#define CLIENTWORKER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDataStream>
#include <QThread>
#include <QFileInfo>

#include <filemanager.h>
class ClientWorker : public QObject
{
    Q_OBJECT
public:
    explicit ClientWorker(QObject *parent = nullptr);
    void initialSynchronization();

signals:
    void finished();
public slots:
    void connectToServer(QString ip, QString port);
private:
    QTcpSocket *socket;
    QString directoryPath;
    FileManager *fileManager;
    QDir directoryToSynchronize;

    void setNumberToContrastFileAndDirectory(int number);
    //void setNumberToQByteArrayHex(QByteArray &targetArray, int size, quint64 number);
    QString getNameOfFileToSend(QString path);

};

#endif // CLIENTWORKER_H
