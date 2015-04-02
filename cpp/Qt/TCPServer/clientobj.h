#ifndef CLIENTOBJ_H
#define CLIENTOBJ_H

#include <QTcpSocket>

class ClientObj : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientObj(QObject *parent = 0);

private slots:
    void readClient();
};

#endif // CLIENTOBJ_H
