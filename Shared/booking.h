#ifndef BOOKING_H
#define BOOKING_H
#include <QString>
#include <QDateTime>
#include <QGeoCoordinate>

class Booking
{
protected:
    QDateTime date;
    QString destination;
    QGeoCoordinate coordinates;

public:
    Booking(QDateTime date, QString destination, QGeoCoordinate coordinates);

    QDateTime GetDate();
    QString GetDestination();
    QGeoCoordinate GetCoordinates();
};

#endif // BOOKING_H
