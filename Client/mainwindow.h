#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "client.h"
#include "useraccount.h"
#include <QGeoCoordinate>

#include <QMainWindow>

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


private slots:

    void on_LoginButton_clicked();

    void on_carBookingButton_clicked();

    void on_planeBookingButton_clicked();

    void on_confirmBookingPlane_clicked();

    void on_confirmBookingCar_clicked();

    void on_carBackToBooking_clicked();

    void on_planeBackToBooking_clicked();

    void CarLocationSet(QString location, double latitude, double longitude);
    void PlaneLocationSet(QString location, double latitude, double longitude);

    void DataReceived(QByteArray bytes);

private:
    Ui::MainWindow *ui;

    Client *client;

    QString address;
    QGeoCoordinate coordinates;

    UserAccount account;

    // Image stuff
    bool waitForImage = false;
    QByteArray imageBytes;
    qsizetype totalImageBytes;
};
#endif // MAINWINDOW_H
