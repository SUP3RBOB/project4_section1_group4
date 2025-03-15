#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QList>
#include <QByteArray>

class Client
{
public:
    Client();

    void Start(QHostAddress ip, qint16 port);

    qint64 Send(char* data);

    void Stop();

    ~Client();

private:
    QTcpSocket *clientSocket;
};

#endif // CLIENT_H
