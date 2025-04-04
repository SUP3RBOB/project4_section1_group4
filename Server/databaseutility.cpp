#include "databaseutility.h"

QSqlQuery DatabaseUtility::InsertCarBooking(UserAccount &account, CarBooking &booking)
{
    QSqlQuery query;
    query.prepare("insert into CarBooking values(?, ?, ?, ?, ?);");
    query.addBindValue(booking.GetDate());
    query.addBindValue(booking.GetDestination());
    query.addBindValue(booking.GetCoordinates().toString());
    query.addBindValue(account.GetEmail());
    query.addBindValue(booking.HasCybertruck());
    return query;
}

QSqlQuery DatabaseUtility::InsertPlaneBooking(UserAccount &account, PlaneBooking &booking)
{
    QSqlQuery query;
    query.prepare("insert into PlaneBooking values(?, ?, ?, ?, ?);");
    query.addBindValue(booking.GetDate());
    query.addBindValue(booking.GetDestination());
    query.addBindValue(booking.GetCoordinates().toString());
    query.addBindValue(account.GetEmail());
    query.addBindValue(booking.GetModel());
    return query;
}
