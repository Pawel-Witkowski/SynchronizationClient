#include "filemanager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}



QByteArray FileManager::exportDataToByteArray()
{
    QByteArray exportArray;
    setNumberToQByteArrayHex(exportArray,8,fileInfo.size());
    exportArray.append(fileInfo.suffix().toUtf8());
    byteArray = exportArray;
    return exportArray;
}

QByteArray FileManager::getByteArray() const
{
    return byteArray;
}

void FileManager::setByteArray(const QByteArray &value)
{
    byteArray = value;
}

QFileInfo FileManager::getFileInfo() const
{
    return fileInfo;
}

void FileManager::setFileInfo(const QString &value)
{
    fileInfo.setFile(value);
}

void FileManager::setNumberToQByteArrayHex(QByteArray &targetArray, int size, quint64 number)
{
    int amountOfZeros;
    if (size == 2){
        amountOfZeros = sizeof(qint32) - QByteArray::number(number,16).length();
    }else if(size==8){
        amountOfZeros = 2* sizeof(qint64) - QByteArray::number(number,16).length();

    }else{
        amountOfZeros = size * sizeof(qint16) - QByteArray::number(number,16).length();
    }
    for (int i=0;i<amountOfZeros;i++){
        targetArray.append('0');
    }
    targetArray.append(QByteArray::number(number,16));
}

