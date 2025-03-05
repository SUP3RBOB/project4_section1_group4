#include <QtTest>
#include "server.h"

// add necessary includes here

class ServerTests : public QObject
{
    Q_OBJECT

private:
    ServerState serverState = ServerState::CarMode;
    void ServerStateChanged(ServerState state);

    QString clientMessage;
    void BytesReceived(QTcpSocket* socket);

public:
    ServerTests();
    ~ServerTests();

private slots:
    void Start_StartsNewServer();
    void Stop_ClosesRunningServer();
    void SetState_ChangesServerState();
    void OnReceivedBytes_GetsInvokedWhenClientSendsMessageToServer();
};

void ServerTests::ServerStateChanged(ServerState state) {
    serverState = state;
}

void ServerTests::BytesReceived(QTcpSocket *socket) {
    clientMessage = socket->readAll();
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
    Server server = Server();
    connect(&server, &Server::OnReceivedBytes, this, &ServerTests::BytesReceived);
    server.Start(QHostAddress::Any, 7770);
    QString expectedMessage = "Hello Guber!";

    // Act
    QTcpSocket clientSocket = QTcpSocket();
    clientSocket.connectToHost(QHostAddress::LocalHost, 7770);

    connect(&clientSocket, &QTcpSocket::connected, this, [&]() {
        clientSocket.write("Hello Guber!");

        // Assert
        QCOMPARE(clientMessage, expectedMessage);
    });

    // Cleanup
    server.Stop();
}

QTEST_APPLESS_MAIN(ServerTests)

#include "tst_servertests.moc"
