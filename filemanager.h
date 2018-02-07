#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QByteArray>
#include <QDateTime>
class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = nullptr);

    QFileInfo getFileInfo() const;
    void setFileInfo(const QString &value);

    QByteArray getByteArray() const;
    void setByteArray(const QByteArray &value);

    static void setNumberToQByteArrayHex(QByteArray &targetArray, int size, quint64 number);
signals:

public slots:
    QByteArray exportDataToByteArray();

private:


    QFileInfo fileInfo;
    QByteArray byteArray;

};

#endif // FILEMANAGER_H
