#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

class Database
{
private:
    QSqlDatabase database;
    static QSqlQuery querySingle;

public:
    Database();

    void Query(const QString& query);
    void Query(QSqlQuery& query);

    bool AccountExists(const QString& email);
};

#endif // DATABASE_H
