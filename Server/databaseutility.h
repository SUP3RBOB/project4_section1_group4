#ifndef DATABASEUTILITY_H
#define DATABASEUTILITY_H

#include <QSqlQuery>
#include "useraccount.h"
#include "carbooking.h"
#include "planebooking.h"

class DatabaseUtility
{
public:
    static QSqlQuery InsertCarBooking(UserAccount& account, CarBooking& booking);
    static QSqlQuery InsertPlaneBooking(UserAccount& account, PlaneBooking& booking);
};

#endif // DATABASEUTILITY_H
