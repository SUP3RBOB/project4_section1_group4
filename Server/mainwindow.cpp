#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QDataStream>
#include "useraccount.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new Server();
    connect(server, &Server::OnStateChanged, this, &MainWindow::ServerStateChanged);

    server->Start(QHostAddress::Any, 7770);

    database = new Database();

    ui->CarBookingTable->setVisible(false);
    ui->PlaneBookingTable->setVisible(false);
}

MainWindow::~MainWindow()
{
    server->Stop();
    delete database;
    delete server;
    delete ui;
}

void MainWindow::BytesReceived(QTcpSocket* socket)
{
    if (socket->bytesAvailable() <= 0) {
        return;
    }

    QByteArray bytes = socket->readAll();
    QDataStream stream = QDataStream(bytes);

    PacketType type;
    stream >> type;

    HandlePacket(socket, stream, type);
}

void MainWindow::HandlePacket(QTcpSocket* socket, QDataStream& stream, PacketType type)
{
    switch (type) {
        case PacketType::StateChange: {
            ServerState state;
            stream >> state;
            server->SetState(state);
        }
        break;

        case PacketType::CarBooking: {
            UserAccount account = UserAccount("", "", 0);
            stream >> account;
        }
        break;

        case PacketType::PlaneBooking: {
            UserAccount account = UserAccount("", "", 0);
            stream >> account;
        }
        break;

        default: // Do literally nothing
        break;
    }
}

void MainWindow::ServerStateChanged(ServerState state)
{
    switch (state) {
        case ServerState::CarMode: {
            ui->CarBookingTable->setVisible(true);
            ui->PlaneBookingTable->setVisible(false);
        }
        break;

        case ServerState::PlaneMode: {
            ui->PlaneBookingTable->setVisible(true);
            ui->CarBookingTable->setVisible(false);
        }
        break;
    }
}

void MainWindow::ClientJoined()
{
    clientCount++;
    ui->ClientCountLabel->setText(QString::number(clientCount));
}

void MainWindow::ClientLeft()
{
    clientCount--;
    ui->ClientCountLabel->setText(QString::number(clientCount));
}
