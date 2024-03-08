#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "elevatorbutton.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{




    ui->setupUi(this);


    connect(ui->pushButton, SIGNAL(released()), this, SLOT (doSomething()));
    connect(ui->openDoorButton, SIGNAL(released()), this, SLOT (openDoorButtonPressed()));
    connect(ui->closeDoorButton, SIGNAL(released()), this, SLOT (closeDoorButtonPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doSomething() {
    qInfo("hello world");
}

void MainWindow::openDoorButtonPressed() {
    emit openDoorSignal();
}

void MainWindow::closeDoorButtonPressed() {
    emit closeDoorSignal();
}

void MainWindow::on_helpButton_released()
{
    emit helpSignal();
}

void MainWindow::on_closeDoorButton_pressed(){

}

