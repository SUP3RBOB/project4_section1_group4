#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "serverstate.h"

/// Contains all functionality required for the server to run.
class Server : public QObject
{
    Q_OBJECT

private:
    QTcpServer* server;
    ServerState state;

    int clientCount = 0;

public:
    /// Creates a new server.
    Server();
    ~Server();

    /// Starts the server with the specified IP address and port.
    bool Start(const QHostAddress& ip, qint16 port);

    /// Stops the server.
    void Stop();

    void Send(QTcpSocket* socket, const QByteArray& bytes);

    /// Sets the state of the server.
    void SetState(ServerState state);

signals:
    /// Invoked when the server receives bytes from client(s).
    void OnReceivedBytes(QTcpSocket* socket);

    /// Invoked when the state of the server changes.
    void OnStateChanged(ServerState state);

    /// Invoked when a client connects or disconnects.
    void OnClientCountUpdated(int count);

private slots:
    void OnClientJoin();
};

#endif // SERVER_H
