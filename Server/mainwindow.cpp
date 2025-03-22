#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new Server();
    connect(server, &Server::OnStateChanged, this, &MainWindow::ServerStateChanged);

    server->Start(QHostAddress::Any, 7770);

    ui->CarBookingTable->setVisible(false);
    ui->PlaneBookingTable->setVisible(false);
}

MainWindow::~MainWindow()
{
    server->Stop();
    delete server;
    delete ui;
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
