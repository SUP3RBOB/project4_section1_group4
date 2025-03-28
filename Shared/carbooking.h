#ifndef CARBOOKING_H
#define CARBOOKING_H

#include "booking.h"

class CarBooking : public Booking
{
private:
    bool cybertruck;

public:
    CarBooking(QDateTime date, QString destination, QGeoCoordinate coordinates, bool cybertruck);

    bool HasCybertruck();

    friend QDataStream& operator <<(QDataStream& stream, const CarBooking& booking);
    friend QDataStream& operator >>(QDataStream& stream, CarBooking& booking);
};

#endif // CARBOOKING_H
