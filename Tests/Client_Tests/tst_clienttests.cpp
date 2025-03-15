#include <QCoreApplication>
#include <QtTest>
#include "client.h"

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
    void test_clientValidQuery();
    void test_clientSerialized();
};

ClientTests::ClientTests() {}

ClientTests::~ClientTests() {}

void ClientTests::test_clientConnectsToServer(){

        //QVERIFY(bool, bool);
        //QCOMAPRE(== , ==);
}

void test_clientDisconnectsTromServer(){


}
void test_clientSendsBytestoServer(){


}
void test_clientValidQuery(){


}
void test_clientSerialized(){


}

QTEST_MAIN(ClientTests)

#include "tst_clienttests.moc"
