#ifndef PLANEBOOKING_H
#define PLANEBOOKING_H

#include "booking.h"

class PlaneBooking : public Booking
{
private:
    QString model;

public:
    PlaneBooking(QDateTime date, QString destination, QGeoCoordinate coordinates, QString model);

    QString GetModel();

    friend QDataStream& operator <<(QDataStream& stream, const PlaneBooking& booking);
    friend QDataStream& operator >>(QDataStream& stream, PlaneBooking& booking);
};

#endif // PLANEBOOKING_H
