#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "serverstate.h"

class Server : public QObject
{
private:
    QTcpServer* server;
    QSet<QTcpSocket*> clients;

    ServerState state;

private slots:
    void OnClientJoin();

public:
    Server();
    ~Server();

    bool Start(const QHostAddress& ip, qint16 port);
    void Stop();


    void SetState(ServerState state);

signals:
    void OnReceivedBytes(QTcpSocket* socket);
    void OnStateChanged(ServerState state);
};

#endif // SERVER_H
