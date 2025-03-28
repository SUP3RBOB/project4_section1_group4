#include "planebooking.h"

PlaneBooking::PlaneBooking(QDateTime date, QString destination, QGeoCoordinate coordinates, QString model)
    : Booking(date, destination, coordinates)
{
    this->model = model;
}

QString PlaneBooking::GetModel()
{
    return model;
}

QDataStream& operator <<(QDataStream& stream, const PlaneBooking& booking) {
    stream << booking.date;
    stream << booking.destination;
    stream << booking.coordinates;
    stream << booking.model;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, PlaneBooking& booking) {
    stream >> booking.date;
    stream >> booking.destination;
    stream >> booking.coordinates;
    stream >> booking.model;
    return stream;
}
