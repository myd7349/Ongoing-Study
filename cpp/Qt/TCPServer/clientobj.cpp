#include <QDataStream>
#include <QByteArray>
#include <QString>

#include <iostream>

#include "clientobj.h"

ClientObj::ClientObj(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}

void ClientObj::readClient()
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_2);
    in.setByteOrder(QDataStream::LittleEndian);

    if (bytesAvailable() < sizeof(qlonglong) * 2) {
        return;
    }

    qlonglong totalSize;
    qlonglong fileNameLen;
    QByteArray fileNameBytes;

    in >> totalSize >> fileNameLen;
    fileNameBytes = read(fileNameLen);
    readAll();

    QString fileName(fileNameBytes);

    std::cout << totalSize << ", "
              << fileNameLen << ", "
              << qPrintable(fileName) << std::endl;
}
