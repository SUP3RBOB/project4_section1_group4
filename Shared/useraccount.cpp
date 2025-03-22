#include "useraccount.h"

UserAccount::UserAccount(const QString &firstName, const QString &lastName, const QString &email) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
}

QString UserAccount::GetFirstName() {
    return firstName;
}

QString UserAccount::GetLastName() {
    return lastName;
}

QString UserAccount::GetEmail() {
    return email;
}

QDataStream& operator <<(QDataStream& stream, const UserAccount& booking) {
    stream << booking.firstName;
    stream << booking.lastName;
    stream << booking.email;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, UserAccount& booking) {
    stream >> booking.firstName;
    stream >> booking.lastName;
    stream >> booking.email;
    return stream;
}
