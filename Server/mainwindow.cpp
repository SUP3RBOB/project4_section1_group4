#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QDataStream>
#include "databaseutility.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    carTicket = QImage(":/images/images/plane_ticket.jpg");
    planeTicket = QImage(":/images/images/plane_ticket.jpg");

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
            UserAccount account = UserAccount();
            CarBooking booking = CarBooking(QDateTime(), "", QGeoCoordinate(), false);
            stream >> account;
            stream >> booking;

            QSqlQuery query = DatabaseUtility::InsertCarBooking(account, booking);
            database->Query(query);

            QByteArray bytes = QByteArray();
            QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
            stream << PacketType::ConfirmationTicket;
            stream << carTicket;
            server->Send(socket, bytes.data());
        }
        break;

        case PacketType::PlaneBooking: {
            UserAccount account = UserAccount();
            PlaneBooking booking = PlaneBooking(QDateTime(), "", QGeoCoordinate(), "");
            stream >> account;
            stream >> booking;

            QSqlQuery query = DatabaseUtility::InsertPlaneBooking(account, booking);
            database->Query(query);

            QByteArray bytes = QByteArray();
            QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
            stream << PacketType::ConfirmationTicket;
            stream << planeTicket;
            server->Send(socket, bytes.data());
        }
        break;

        case PacketType::AccountCheck: {
            UserAccount account;
            stream >> account;

            bool exists = database->AccountExists(account.GetEmail(), account.GetPassword());

            QByteArray bytes = QByteArray();
            QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
            stream << PacketType::AccountConfirmed;
            stream << exists;
            server->Send(socket, bytes.data());
        }

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
