#include "carbooking.h"

CarBooking::CarBooking(QDateTime date, QString destination, QGeoCoordinate coordinates, bool cybertruck)
    : Booking(date, destination, coordinates)
{
    this->cybertruck = cybertruck;
}

bool CarBooking::HasCybertruck()
{
    return cybertruck;
}

QDataStream& operator <<(QDataStream& stream, const CarBooking& booking) {
    stream << booking.date;
    stream << booking.destination;
    stream << booking.coordinates;
    stream << booking.cybertruck;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, CarBooking& booking) {
    stream >> booking.date;
    stream >> booking.destination;
    stream >> booking.coordinates;
    stream >> booking.cybertruck;
    return stream;
}
