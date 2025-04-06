#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "database.h"
#include "packettype.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Server* server;
    Database* database;

    int clientCount = 0;

    void HandlePacket(QTcpSocket* socket, QDataStream& stream, PacketType type);
    void UpdateCarTable();
    void UpdatePlaneTable();

private slots:
    void BytesReceived(QTcpSocket* socket);
    void ServerStateChanged(ServerState state);
    void ClientCountUpdated(int count);
};
#endif // MAINWINDOW_H
