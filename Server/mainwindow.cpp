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
    connect(server, &Server::OnReceivedBytes, this, &MainWindow::BytesReceived);
    connect(server, &Server::OnClientCountUpdated, this, &MainWindow::ClientCountUpdated);

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
            server->Send(socket, bytes);

            UpdateCarTable();
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
            server->Send(socket, bytes);
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
            server->Send(socket, bytes);
        }

        default: // Do literally nothing
        break;
    }
}

void MainWindow::UpdateCarTable()
{
    ui->CarBookingTable->clear();

    QSqlQuery query;
    query.prepare("select user_email, destination_address, coordinates, booking_date, is_cybertruck from CarBooking order by booking_date desc;");
    database->Query(query);

    while (query.next()) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, query.value(0).toString());
        item->setText(1, query.value(1).toString());
        item->setText(2, query.value(2).toString());
        item->setText(3, query.value(3).toString());
        item->setText(4, query.value(4).toString() == "1" ? "true" : "false");
        ui->CarBookingTable->addTopLevelItem(item);
    }
}

void MainWindow::UpdatePlaneTable()
{
    ui->CarBookingTable->clear();

    QSqlQuery query;
    query.prepare("select user_email, destination_address, coordinates, booking_date, model from PlaneBooking order by booking_date desc;");
    database->Query(query);

    while (query.next()) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, query.value(0).toString());
        item->setText(1, query.value(1).toString());
        item->setText(2, query.value(2).toString());
        item->setText(3, query.value(3).toString());
        item->setText(4, query.value(4).toString());
        ui->CarBookingTable->addTopLevelItem(item);
    }
}

void MainWindow::ServerStateChanged(ServerState state)
{
    switch (state) {
        case ServerState::CarMode: {
            ui->CarBookingTable->setVisible(true);
            ui->PlaneBookingTable->setVisible(false);
            UpdateCarTable();
        }
        break;

        case ServerState::PlaneMode: {
            ui->PlaneBookingTable->setVisible(true);
            ui->CarBookingTable->setVisible(false);
            UpdatePlaneTable();
        }
        break;
    }
}

void MainWindow::ClientCountUpdated(int count)
{
    QString text;
    QTextStream(&text) << "Clients Connected: " << count;
    ui->ClientCountLabel->setText(text);
}
