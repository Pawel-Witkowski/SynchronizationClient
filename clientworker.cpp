#include "clientworker.h"

ClientWorker::ClientWorker(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    //directoryPath = "/Users/p.witkowski/Documents/XXX";
    directoryPath = "C:\\Users\\Pawel\\Documents\\xxx";
    fileManager = new FileManager(this);
}



void ClientWorker::connectToServer(QString ip, QString port)
{
    socket->connectToHost(ip,port.toInt());
    if (socket->waitForConnected()) initialSynchronization();

}


void ClientWorker::initialSynchronization()
{
    qDebug() << "started to synchronize...";
    directoryToSynchronize.setPath(directoryPath);

   // QDirIterator walker("/Users/p.witkowski/Documents/XXX", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);


    QFileInfo info;
    QByteArray fileInfoArray;
    QByteArray fileData;
    QString nameOfFile;
    QDirIterator walker("C:\\Users\\Pawel\\Documents\\xxx", QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(walker.hasNext()){

        walker.next();
        fileData.clear();
        info.setFile(walker.filePath());
        setNumberToContrastFileAndDirectory(1);



        nameOfFile = getNameOfFileToSend(walker.filePath());
        FileManager::setNumberToQByteArrayHex(fileData,2,nameOfFile.toUtf8().length());
        socket->write(fileData);
        fileData.clear();

        socket->write(nameOfFile.toUtf8());
        socket->waitForBytesWritten();

        qDebug() << "Sent FileName " + nameOfFile;
        fileManager->setFileInfo(walker.filePath());

        fileInfoArray=fileManager->exportDataToByteArray();
        FileManager::setNumberToQByteArrayHex(fileData,1,fileInfoArray.length());
        socket->write(fileData);
        socket->write(fileInfoArray);


        socket->waitForReadyRead();
        int respond = socket->read(sizeof(qint8)).toInt();

        if (respond == 1){
            QFile file(info.filePath());
            file.open(QIODevice::ReadOnly);
            qDebug() << "Sending file...";
            socket->write(file.readAll());
            socket->waitForBytesWritten();
            qDebug() << "File sent!";
            file.close();
        }else{
            qDebug() << "File rejected";
        }




    }
    QDirIterator walkerDir("C:\\Users\\Pawel\\Documents\\xxx", QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

   // QDirIterator walkerDir("/Users/p.witkowski/Documents/XXX", QDir::Dirs | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(walkerDir.hasNext()){
        fileData.clear();
        walkerDir.next();

        info.setFile(walkerDir.filePath());
        setNumberToContrastFileAndDirectory(2);

        nameOfFile = getNameOfFileToSend(walkerDir.filePath());


        FileManager::setNumberToQByteArrayHex(fileData,2,nameOfFile.toUtf8().length());
        socket->write(fileData);

        socket->write(nameOfFile.toUtf8());
        socket->waitForBytesWritten();



    }



}

void ClientWorker::setNumberToContrastFileAndDirectory(int number)
{
    socket->write(QByteArray::number(number));
}


QString ClientWorker::getNameOfFileToSend(QString path)
{
    return path.remove(directoryToSynchronize.path()+"/");
}
