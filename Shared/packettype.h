#ifndef PACKETTYPE_H
#define PACKETTYPE_H

enum class PacketType {
    StateChange,
    CarBooking,
    PlaneBooking,
    ConfirmationTicket,
    AccountCheck,
    AccountConfirmed
};

#endif // PACKETTYPE_H
