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
