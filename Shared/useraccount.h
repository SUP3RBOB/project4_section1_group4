#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include <QString>
#include <QDataStream>

/// Represents a user account in the application.
class UserAccount
{
private:
    QString email;
    QString password;

public:
    /// Constructs a blank user
    UserAccount();

    /// Constructs a new user account.
    UserAccount(const QString& email, const QString& password);

    /// Gets the user's email.
    QString GetEmail();

    QString GetPassword();

    friend QDataStream& operator <<(QDataStream& stream, const UserAccount& booking);
    friend QDataStream& operator >>(QDataStream& stream, UserAccount& booking);
};

#endif // USERACCOUNT_H
