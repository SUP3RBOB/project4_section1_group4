#include <QtTest>

// add necessary includes here

class ExampleTests : public QObject
{
    Q_OBJECT

public:
    ExampleTests();
    ~ExampleTests();

private slots:
    void Example1();
    void Example2();
    void Example3();
    void Example4();
};

ExampleTests::ExampleTests() {}

ExampleTests::~ExampleTests() {}

void ExampleTests::Example1()
{
    // Arrange
    int actual = 2 + 3;
    int expected = 5;

    // Assert
    QCOMPARE(actual, expected);
}

void ExampleTests::Example2()
{
    // Arrange
    QString actual = QString("Hello ") + QString("World!");
    QString expected = "Hello World!";

    // Assert
    QCOMPARE(actual, expected);
}

void ExampleTests::Example3()
{
    // Act
    bool actual = true;

    // Assert
    QVERIFY(actual);
}

void ExampleTests::Example4()
{
    // Arrange
    int actual = 2 + 3;
    int expected = 5;

    // Assert
    QVERIFY(actual == expected);
}

QTEST_APPLESS_MAIN(ExampleTests)

#include "tst_exampletests.moc"
