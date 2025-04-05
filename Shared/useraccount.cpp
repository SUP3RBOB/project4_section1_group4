#include "useraccount.h"

UserAccount::UserAccount()
{
    email = "";
    password = "";
}

UserAccount::UserAccount(const QString &email, const QString& password) {
    this->email = email;
    this->password = password;
}

QString UserAccount::GetEmail() {
    return email;
}

QString UserAccount::GetPassword()
{
    return password;
}

QDataStream& operator <<(QDataStream& stream, const UserAccount& booking) {
    stream << booking.email;
    stream << booking.password;
    return stream;
}

QDataStream& operator >>(QDataStream& stream, UserAccount& booking) {
    stream >> booking.email;
    stream >> booking.password;
    return stream;
}
