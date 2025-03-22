#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server.h"
#include "database.h"

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

private slots:
    void ServerStateChanged(ServerState state);
    void ClientJoined();
    void ClientLeft();
};
#endif // MAINWINDOW_H
