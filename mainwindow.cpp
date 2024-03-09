#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "elevatorbutton.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    //connect(ui->pushButton, SIGNAL(released()), this, SLOT (doSomething()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_powerOutButton_released()
{
    emit powerOut();
}

void MainWindow::on_fireButton_released()
{
    emit fire();
}

