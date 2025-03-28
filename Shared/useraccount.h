#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QString>
#include <QDataStream>

/// Represents a user account in the application.
class UserAccount
{
private:
    QString firstName;
    QString lastName;
    QString email;

public:
    /// Constructs a new user account.
    UserAccount(const QString& firstName, const QString& lastName, const QString& email);

    /// Gets the user's first name.
    QString GetFirstName();

    /// Gets the user's last name.
    QString GetLastName();

    /// Gets the user's email.
    QString GetEmail();

    friend QDataStream& operator <<(QDataStream& stream, const UserAccount& booking);
    friend QDataStream& operator >>(QDataStream& stream, UserAccount& booking);
};

#endif // USERACCOUNT_H
