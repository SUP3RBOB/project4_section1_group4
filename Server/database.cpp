#include "database.h"

Database::Database() {
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setPort(3306);
    database.setDatabaseName("guberbase");
    database.setUserName("root");

    bool success = database.open();
    if (success) {
        querySingle = QSqlQuery(database);
        qDebug() << "Successfully connected to database";
    } else {
        qDebug() << "Failed to connect to database";
    }
}

Database::~Database()
{
    database.close();
}

bool Database::Query(const QString& query)
{
    return querySingle.exec(query);
}

bool Database::Query(QSqlQuery& query)
{
    return query.exec();
}

bool Database::AccountExists(const QString& email)
{
    querySingle.prepare("select count(*) from UserAccount where email like ?;");
    querySingle.addBindValue(email);
    querySingle.exec();
    querySingle.next();

    return querySingle.value(0).toInt() > 0;
}
