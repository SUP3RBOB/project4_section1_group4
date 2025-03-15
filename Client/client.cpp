#include "client.h"

Client::Client() {

    clientSocket = new QTcpSocket();
}

void Client::Start(QHostAddress ip, qint16 port){

    clientSocket->connectToHost(ip, port);
}

qint64 Client::Send(char* data){

    return clientSocket->write(data);
}

void Client::Stop(){

    clientSocket->disconnectFromHost();
}

Client::~Client(){

    delete clientSocket;
}

