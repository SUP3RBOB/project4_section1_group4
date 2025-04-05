#include "server.h"
#include <QTcpSocket>

Server::Server() {
    server = new QTcpServer();
    state = ServerState::CarMode;

    connect(server, &QTcpServer::newConnection, this, &Server::OnClientJoin);
}

Server::~Server() {
    delete server;
}

bool Server::Start(const QHostAddress& ip, qint16 port) {
    return server->listen(ip, port);
}

void Server::Stop() {
    server->close();
}

void Server::Send(QTcpSocket *socket, const QByteArray& bytes)
{
    socket->write(bytes);
}

void Server::SetState(ServerState state) {
    this->state = state;
    emit OnStateChanged(state);
}

void Server::OnClientJoin() {
    QTcpSocket* clientSocket = server->nextPendingConnection();
    qDebug() << "Client Connected";
    emit OnClientConnected();

    connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
        qDebug() << "yes";
        emit OnReceivedBytes(clientSocket);
    });

    connect(clientSocket, &QTcpSocket::disconnected, this, [this]() {
        emit OnClientDisconnected();
    });
}
