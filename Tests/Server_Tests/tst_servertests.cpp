#include <QCoreApplication>
#include <QtTest>
#include "server.h"

// add necessary includes here

class ServerTests : public QObject
{
    Q_OBJECT

private:
    ServerState serverState = ServerState::CarMode;
    void ServerStateChanged(ServerState state);

public:
    ServerTests();
    ~ServerTests();

private slots:
    void Start_StartsNewServer();
    void Stop_ClosesRunningServer();
    void SetState_ChangesServerState();
    void OnReceivedBytes_GetsInvokedWhenClientSendsMessageToServer();
    void OnClientCountUpdated_InvokedWhenClientConnects();
    void Send_SendsBytesToClient();
};

void ServerTests::ServerStateChanged(ServerState state) {
    serverState = state;
}

ServerTests::ServerTests() {}

ServerTests::~ServerTests() {}

void ServerTests::Start_StartsNewServer() {
    // Arrange
    Server server = Server();

    // Act
    server.Start(QHostAddress::Any, 7770);

    // Assert
    QTcpServer test = QTcpServer();
    QVERIFY(!test.listen(QHostAddress::Any, 7770));

    // Cleanup
    server.Stop();
    test.close();
}

void ServerTests::Stop_ClosesRunningServer() {
    // Arrange
    Server server = Server();
    server.Start(QHostAddress::Any, 7770);

    // Act
    server.Stop();

    // Assert
    QTcpServer test = QTcpServer();
    QVERIFY(test.listen(QHostAddress::Any, 7770));

    // Cleanup
    test.close();
}

void ServerTests::SetState_ChangesServerState() {
    // Arrange
    Server server = Server();
    connect(&server, &Server::OnStateChanged, this, &ServerTests::ServerStateChanged);
    ServerState expectedState = ServerState::PlaneMode;

    // Act
    server.SetState(ServerState::PlaneMode);

    // Assert
    QCOMPARE(serverState, expectedState);
}

void ServerTests::OnReceivedBytes_GetsInvokedWhenClientSendsMessageToServer() {
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);

    Server server = Server();
    QString actualMessage;
    QString expectedMessage = "Hello Guber!";
    connect(&server, &Server::OnReceivedBytes, this, [&](QTcpSocket* socket) {
        // Assert
        actualMessage = socket->readAll();
        QCOMPARE(actualMessage, expectedMessage);
        server.Stop();
        a.quit();
    });

    server.Start(QHostAddress::Any, 7770);

    // Act
    QTcpSocket clientSocket = QTcpSocket();
    clientSocket.connectToHost(QHostAddress::LocalHost, 7770);
    connect(&clientSocket, &QTcpSocket::connected, this, [&]() {
        clientSocket.write("Hello Guber!");
    });

    a.exec();
}

void ServerTests::OnClientCountUpdated_InvokedWhenClientConnects()
{
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);

    Server server = Server();
    connect(&server, &Server::OnClientCountUpdated, this, [&](int count) {
        // Assert
        qDebug() << count;
        QVERIFY(count > 0);
        disconnect(&server, nullptr, nullptr, nullptr);
        server.Stop();
        a.quit();
    });

    server.Start(QHostAddress::Any, 7771);

    // Act
    QTcpSocket clientSocket = QTcpSocket();
    clientSocket.connectToHost(QHostAddress::LocalHost, 7771);

    a.exec();
}

void ServerTests::Send_SendsBytesToClient()
{
    // Arrange
    int argc = 0;
    QCoreApplication a = QCoreApplication(argc, nullptr);
    QString expectedMessage = "Hello Client!";

    Server server = Server();
    server.Start(QHostAddress::Any, 7772);
    connect(&server, &Server::OnReceivedBytes, this, [&](QTcpSocket* cs) {
        server.Send(cs, QByteArray("Hello Client!").data());
    });

    // Act
    QTcpSocket clientSocket = QTcpSocket();
    connect(&clientSocket, &QTcpSocket::connected, this, [&]() {
        clientSocket.write("I'm Here");
    });

    connect(&clientSocket, &QTcpSocket::readyRead, this, [&]() {
        QByteArray bytes = clientSocket.readAll();
        QCOMPARE(bytes, expectedMessage.toUtf8());
        server.Stop();
        a.quit();
    });
    clientSocket.connectToHost(QHostAddress::LocalHost, 7772);

    a.exec();
}

QTEST_APPLESS_MAIN(ServerTests)

#include "tst_servertests.moc"
