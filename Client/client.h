#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QList>
#include <QByteArray>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();

    void Start(QHostAddress ip, qint16 port);

    qint64 Send(const QByteArray& data);

    void Stop();

    ~Client();

private:
    QTcpSocket *clientSocket;

signals:
    void OnDataReceived(QByteArray bytes);
};

#endif // CLIENT_H
