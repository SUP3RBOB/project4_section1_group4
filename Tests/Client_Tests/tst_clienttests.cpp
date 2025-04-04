#include <QCoreApplication>
#include <QtTest>
#include "client.h"
#include <QTcpServer>

// add necessary includes here

class ClientTests : public QObject
{
    Q_OBJECT

public:
    ClientTests();
    ~ClientTests();

private slots:
    void test_clientConnectsToServer();
    void test_clientDisconnectsTromServer();
    void test_clientSendsBytestoServer();
    void OnDataReceived_ObtainsDataFromServer();
};

ClientTests::ClientTests() {}

ClientTests::~ClientTests() {}

void ClientTests::test_clientConnectsToServer(){
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);
    Client client = Client();
    QTcpServer server = QTcpServer();
    connect(&server, &QTcpServer::newConnection, this, [&]() {
        // Assert
        QVERIFY(true);
        server.close();
        client.Stop();
        a.quit();
    });
    server.listen(QHostAddress::Any, 7777);

    // Act
    client.Start(QHostAddress::LocalHost, 7777);

    a.exec();
}

void ClientTests::test_clientDisconnectsTromServer() {
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);
    Client client = Client();
    QTcpServer server = QTcpServer();
    connect(&server, &QTcpServer::newConnection, this, [&]() {
        QTcpSocket* socket = server.nextPendingConnection();
        connect(socket, &QTcpSocket::disconnected, this, [&]() {
            // Assert
            QVERIFY(true);
            server.close();
            a.quit();
        });

        // Act
        client.Stop();
    });

    server.listen(QHostAddress::Any, 7778);
    client.Start(QHostAddress::LocalHost, 7778);

    a.exec();
}

void ClientTests::test_clientSendsBytestoServer(){
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);
    Client client = Client();
    QTcpServer server = QTcpServer();
    QString expectedMessage = "Hello Server!";
    connect(&server, &QTcpServer::newConnection, this, [&]() {
        QTcpSocket* socket = server.nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, [&](){
            // Assert
            QString actual = socket->readAll();
            QCOMPARE(actual, expectedMessage);
            server.close();
            client.Stop();
            a.quit();
        });

        // Act
        QByteArray bytes = "Hello Server!";
        client.Send(bytes.data());
    });

    server.listen(QHostAddress::Any, 7779);
    client.Start(QHostAddress::LocalHost, 7779);

    a.exec();
}

void ClientTests::OnDataReceived_ObtainsDataFromServer()
{
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);
    Client client = Client();
    QTcpServer server = QTcpServer();
    QByteArray expectedMessage = "Hello Client!";
    connect(&server, &QTcpServer::newConnection, this, [&]() {
        // Act
        QTcpSocket* socket = server.nextPendingConnection();
        QByteArray bytes = "Hello Client!";
        socket->write(bytes.data());
    });

    connect(&client, &Client::OnDataReceived, this, [&](QByteArray bytes){
        // Assert
        QCOMPARE(bytes, expectedMessage);
        server.close();
        client.Stop();
        a.quit();
    });

    server.listen(QHostAddress::Any, 7779);
    client.Start(QHostAddress::LocalHost, 7779);

    a.exec();
}

QTEST_MAIN(ClientTests)

#include "tst_clienttests.moc"
