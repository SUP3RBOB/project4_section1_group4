#include "client.h"

Client::Client() {
    clientSocket = new QTcpSocket();
    connect(clientSocket, &QTcpSocket::readyRead, this, [this]() {
        emit OnDataReceived(clientSocket->readAll());
    });
}

void Client::Start(QHostAddress ip, qint16 port){

    clientSocket->connectToHost(ip, port);
}

qint64 Client::Send(const QByteArray& data){
    return clientSocket->write(data);
}

void Client::Stop(){

    clientSocket->disconnectFromHost();
}

Client::~Client(){

    delete clientSocket;
}

