#include "clientobj.h"
#include "serverobj.h"

ServerObj::ServerObj(QObject *parent) :
    QTcpServer(parent)
{
}

void ServerObj::incomingConnection(qintptr sockDescriptor)
{
    ClientObj *socket = new ClientObj(this);
    socket->setSocketDescriptor(sockDescriptor);
}
