#include <QCoreApplication>
#include <QtTest>
#include "database.h"

// add necessary includes here

class DatabaseTests : public QObject
{
    Q_OBJECT
private:
    Database* db;

public:
    DatabaseTests();
    ~DatabaseTests();

private slots:
    void Constructor_ConnectsToMySQLDatabase();
    void Constructor_SetsDataBaseValues();
    void Destructor_ClosesDatabase();
    void AccountExists_ReturnsTrueWhenAccountInDatabase();
    void AccountExists_ReturnsFalseWhenAccountNotInDatabase();
    void Query_WithStringAndValidQuery_ReturnsTrue();
    void Query_WithStringAndInvalidQuery_ReturnsFalse();
    void Query_WithObjectAndValidQuery_ReturnsTrue();
    void Query_WithObjectAndInvalidQuery_ReturnsFalse();
};

DatabaseTests::DatabaseTests() : db(new Database()) {}

DatabaseTests::~DatabaseTests() {
    delete db;
}

void DatabaseTests::Constructor_ConnectsToMySQLDatabase()
{
    // Arrange
    QSqlDatabase database = QSqlDatabase::database();

    // Assert
    QVERIFY(database.isOpen());
}

void DatabaseTests::Constructor_SetsDataBaseValues()
{
    // Arrange
    QSqlDatabase database = QSqlDatabase::database();
    QString expectedHostName = "localhost";
    int expectedPort = 3306;
    QString expectedDatabaseName = "guberbase";
    QString expectedUserName = "root";
    QString expectedPassword = "";
    QString expectedDriver = "QMYSQL";

    // Assert
    QCOMPARE(database.hostName(), expectedHostName);
    QCOMPARE(database.port(), expectedPort);
    QCOMPARE(database.databaseName(), expectedDatabaseName);
    QCOMPARE(database.userName(), expectedUserName);
    QCOMPARE(database.password(), expectedPassword);
    QCOMPARE(database.driverName(), expectedDriver);
}

void DatabaseTests::Destructor_ClosesDatabase()
{
    // Arrange
    QSqlDatabase database = QSqlDatabase::database();

    // Act
    delete db;

    // Assert
    QVERIFY(!database.isOpen());

    // Cleanup
    db = new Database();
}

void DatabaseTests::AccountExists_ReturnsTrueWhenAccountInDatabase()
{
    // Act
    bool success = db->AccountExists("admin@guber.ca");

    // Assert
    QVERIFY(success);
}

void DatabaseTests::AccountExists_ReturnsFalseWhenAccountNotInDatabase()
{
    // Act
    bool success = db->AccountExists("email@email.com");

    // Assert
    QVERIFY(!success);
}

void DatabaseTests::Query_WithStringAndValidQuery_ReturnsTrue()
{
    // Act
    bool success = db->Query("select * from UserAccount;");

    // Assert
    QVERIFY(success);
}

void DatabaseTests::Query_WithStringAndInvalidQuery_ReturnsFalse()
{
    // Act
    bool success = db->Query("select * from UserAcccccccount;");

    // Assert
    QVERIFY(!success);
}

void DatabaseTests::Query_WithObjectAndValidQuery_ReturnsTrue()
{
    // Arrange
    QSqlQuery query;
    query.prepare("select * from UserAccount;");

    // Act
    bool success = db->Query(query);

    // Assert
    QVERIFY(success);
}

void DatabaseTests::Query_WithObjectAndInvalidQuery_ReturnsFalse()
{
    // Arrange
    QSqlQuery query;
    query.prepare("select * from UserAcccccccount;");

    // Act
    bool success = db->Query(query);

    // Assert
    QVERIFY(!success);
}

QTEST_MAIN(DatabaseTests)

#include "tst_databasetests.moc"
