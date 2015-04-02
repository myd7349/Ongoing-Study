#ifndef SERVEROBJ_H
#define SERVEROBJ_H

#include <QTcpServer>

class ServerObj : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerObj(QObject *parent = 0);

private:
    void incomingConnection(qintptr sockDescriptor);

};

#endif // SERVEROBJ_H
