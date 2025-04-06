#include "booking.h"

Booking::Booking(QDateTime date, QString destination, QGeoCoordinate coordinates) {
    this->date = date;
    this->destination = destination;
    this->coordinates = coordinates;
}

QDateTime Booking::GetDate()
{
    return date;
}

QString Booking::GetDestination()
{
    return destination;
}

QString Booking::GetCoordinates()
{
    QString coords;
    QTextStream(&coords) << "(" << coordinates.latitude() << ", " << coordinates.longitude() << ")";
    return coords;
}
