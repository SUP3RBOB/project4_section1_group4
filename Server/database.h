#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
private:
    QSqlDatabase database;
    QSqlQuery querySingle;

public:
    Database();
    ~Database();

    bool Query(const QString& query);
    bool Query(QSqlQuery& query);

    bool AccountExists(const QString& email);
};

#endif // DATABASE_H
