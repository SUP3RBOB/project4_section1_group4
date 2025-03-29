#include "Login.h"
#include "ui_Login.h"
#include "QMessageBox"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_LoginButton_clicked()
{
    QString name = "GuberCEO";
    QString password = "123";

    QString userInputName = ui->userName->text();
    QString userInputPassword = ui->userPassword->text();


    if (name == userInputName && password == userInputPassword) {
        //::information(this, "Welcome User", "User: " +userInputName+ "\nWelcome to GUBER!");
        ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);
    }
    else {
        QMessageBox::information(this, "Error Message", "invalid username or password please try again");
    }
}


void MainWindow::on_carBookingButton_clicked()
{
    ui->GuberWidget->setCurrentIndex(CAR_BOOKING_PAGE);
}


void MainWindow::on_planeBookingButton_clicked()
{
     ui->GuberWidget->setCurrentIndex(PLANE_BOOKING_PAGE);
}


void MainWindow::on_confirmBookingPlane_clicked()
{
    ui->GuberWidget->setCurrentIndex(CONFIRMATION_PAGE);
}


void MainWindow::on_confirmBookingCar_clicked()
{
    ui->GuberWidget->setCurrentIndex(CONFIRMATION_PAGE);
}


void MainWindow::on_carBackToBooking_clicked()
{
    ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);
}


void MainWindow::on_planeBackToBooking_clicked()
{
    ui->GuberWidget->setCurrentIndex(BOOKING_PAGE);
}

