#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>

/// Contains all functionality required for usage of database.
class Database
{
private:
    QSqlDatabase database;
    QSqlQuery querySingle;

public:
    /// Connects to the MySQL database.
    Database();
    ~Database();

    /// Runs a query with the specified string.
    bool Query(const QString& query);

    /// Runs a query with the specified query object.
    bool Query(QSqlQuery& query);

    bool AccountExists(const QString& email, const QString password);
};

#endif // DATABASE_H
