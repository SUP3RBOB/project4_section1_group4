#ifndef LOGIN_H
#define LOGIN_H

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

private:
    Ui::MainWindow *ui;
};
#endif // LOGIN_H
