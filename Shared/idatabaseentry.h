#ifndef IDATABASEENTRY_H
#define IDATABASEENTRY_H

#include <QSqlQuery>

/// Interface for allowing classes to be added to the database.
class IDatabaseEntry {
public:
    virtual QSqlQuery GetInsertQuery() = 0;
};

#endif // IDATABASEENTRY_H
