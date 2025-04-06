#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "useraccount.h"
#include <packettype.h>
#include "serverstate.h"
#include "carbooking.h"
#include "planebooking.h"
#include <QFile>

#define BOOKING_PAGE 1
#define CAR_BOOKING_PAGE 2
#define PLANE_BOOKING_PAGE 3
#define CONFIRMATION_PAGE 4

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->LoginButton, SIGNAL(clicked()), this, SLOT(on_LoginButton_clicked()));

    client = new Client();
    client->Start(QHostAddress::LocalHost, 7770);

    connect(client, SIGNAL(OnDataReceived(QByteArray)), this, SLOT(DataReceived(QByteArray)));

    ui->CarMapView->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    QObject* carMapObj = (QObject*)ui->CarMapView->rootObject();
    connect(carMapObj, SIGNAL(markerPositionChanged(QString, double, double)), this, SLOT(CarLocationSet(QString, double, double)));
    ui->CarMapView->show();

    ui->PlaneMapView->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
    QObject* planeMapObj = (QObject*)ui->PlaneMapView->rootObject();
    connect(planeMapObj, SIGNAL(markerPositionChanged(QString, double, double)), this, SLOT(PlaneLocationSet(QString, double, double)));
    ui->PlaneMapView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete client;
}


void MainWindow::on_LoginButton_clicked()
{
    QString userInputEmail = ui->userEmail->text();
    QString userInputPassword = ui->userPassword->text();

    account = UserAccount(userInputEmail, userInputPassword);

    QByteArray bytes = QByteArray();
    QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
    stream << PacketType::AccountCheck;
    stream <<  account;
    client->Send(bytes);
}


void MainWindow::on_carBookingButton_clicked()
{
    ui->GuberWidget->setCurrentIndex(CAR_BOOKING_PAGE);

    QByteArray bytes = QByteArray();
    QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
    stream << PacketType::StateChange;
    stream <<  ServerState::CarMode;
    client->Send(bytes);
}


void MainWindow::on_planeBookingButton_clicked()
{
     ui->GuberWidget->setCurrentIndex(PLANE_BOOKING_PAGE);

    QByteArray bytes = QByteArray();
    QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
    stream << PacketType::StateChange;
    stream <<  ServerState::PlaneMode;
    client->Send(bytes);
}


void MainWindow::on_confirmBookingPlane_clicked()
{
    ui->GuberWidget->setCurrentIndex(CONFIRMATION_PAGE);

    PlaneBooking planeBooking(QDateTime::currentDateTime(), address, coordinates, ui->planeChoices->currentText()) ;

    QByteArray bytes = QByteArray();
    QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
    stream << PacketType::PlaneBooking;
    stream << account;
    stream << planeBooking;
    client->Send(bytes);
}


void MainWindow::on_confirmBookingCar_clicked()
{
    ui->GuberWidget->setCurrentIndex(CONFIRMATION_PAGE);

    CarBooking carBooking(QDateTime::currentDateTime(), address, coordinates, ui->cyberTruckBox->checkState()== Qt::Checked);

    QByteArray bytes = QByteArray();
    QDataStream stream = QDataStream(&bytes, QIODeviceBase::WriteOnly);
    stream << PacketType::CarBooking;
    stream << account;
    stream << carBooking;
    client->Send(bytes);
}


void MainWindow::on_carBackToBooking_clicked()
{
    ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);
}


void MainWindow::on_planeBackToBooking_clicked()
{
    ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);
}

void MainWindow::CarLocationSet(QString location, double latitude, double longitude)
{
    qDebug() << location;
    qDebug() << "(" << latitude << ", " << longitude << ")";
    ui->LocationLabelCar->setText(location);
    address = location;
    coordinates = QGeoCoordinate(latitude, longitude);
}

void MainWindow::PlaneLocationSet(QString location, double latitude, double longitude)
{
    qDebug() << location;
    qDebug() << "(" << latitude << ", " << longitude << ")";
    ui->locationLabelPlane->setText(location);
    address = location;
    coordinates = QGeoCoordinate(latitude, longitude);
}

void MainWindow::DataReceived(QByteArray bytes)
{
    if (waitForImage) {
        imageBytes.append(bytes);
        qDebug() << imageBytes.size() << "/" << totalImageBytes;

        if (imageBytes.size() >= totalImageBytes) {
            QPixmap ticket;
            ticket.loadFromData(imageBytes);
            ui->ConfirmationTicket->setPixmap(ticket);
            waitForImage = false;
        }

        return;
    }

    QDataStream stream = QDataStream(bytes);
    PacketType type;
    stream >> type;

    if(type == PacketType::AccountConfirmed){
        bool accountConfrimed;

        stream >> accountConfrimed;

        if(accountConfrimed == true)
            ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);

        else
            QMessageBox::information(this, "Error Message", "invalid username or password please try again");
    }
    else if (type == PacketType::ConfirmationTicket) {
        waitForImage = true;
        stream >> totalImageBytes;
        imageBytes = QByteArray();
    }
}
