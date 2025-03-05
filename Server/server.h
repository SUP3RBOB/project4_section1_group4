#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "serverstate.h"

class Server : public QObject
{
    Q_OBJECT

private:
    QTcpServer* server;
    ServerState state;

public:
    Server();
    ~Server();

    bool Start(const QHostAddress& ip, qint16 port);
    void Stop();


    void SetState(ServerState state);

signals:
    void OnReceivedBytes(QTcpSocket* socket);
    void OnStateChanged(ServerState state);

private slots:
    void OnClientJoin();

};

#endif // SERVER_H
