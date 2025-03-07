#include "database.h"

Database::Database() {
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setPort(3306);
    database.setUserName("root");
    bool success = database.open();
    if (!success) {
        qDebug() << "Failed to connect to database";
    }
}

void Database::Query(const QString& query)
{
    querySingle.exec(query);
}

void Database::Query(QSqlQuery& query)
{
    query.exec();
}

bool Database::AccountExists(const QString &email)
{
    querySingle.prepare("select count(email) from UserAccount where email like ':email';");
    querySingle.bindValue(":email", email);
}
