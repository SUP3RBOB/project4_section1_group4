#include "server.h"
#include <QTcpSocket>

Server::Server() {
    server = new QTcpServer();
    clients = QSet<QTcpSocket*>();
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

void Server::SetState(ServerState state) {
    this->state = state;
    emit OnStateChanged(state);
}

void Server::OnClientJoin() {
    QTcpSocket* clientSocket = server->nextPendingConnection();
    if (!clients.contains(clientSocket)) {
        clients.insert(clientSocket);

        connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
            emit OnReceivedBytes(clientSocket);
        });

        connect(clientSocket, &QAbstractSocket::stateChanged, this, [this, clientSocket](QAbstractSocket::SocketState state) {
            if (state == QAbstractSocket::ClosingState) {
                clients.remove(clientSocket);
            }
        });
    }
}
