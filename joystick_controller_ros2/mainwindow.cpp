#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "joystick.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

//    joystick joystick;
//    joystick.setModal(true);
//    joystick.exec();
    hide();
    joystick_panel = new joystick(this);
    joystick_panel->show();

//    joystick *joystick_panel = new joystick();

       // Connect joystickMoved signal to a lambda function
       QObject::connect(joystick_panel, &joystick::joystickMoved, [](double xPercent, double yPercent) {
           qDebug() << "Joystick moved to:" << xPercent << yPercent;
       });

}

