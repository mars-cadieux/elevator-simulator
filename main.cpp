#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Controller control;

    //Elevator e1;
    //Elevator e2;
    //Building b;



    //MainWindow w1;
    ////MainWindow w2;

    //QObject::connect(&w1, &MainWindow::openDoorSignal, &e1, &Elevator::openDoor, Qt::QueuedConnection);
    //QObject::connect(&w1, &MainWindow::closeDoorSignal, &e1, &Elevator::closeDoor, Qt::QueuedConnection);
    //QObject::connect(&w1, &MainWindow::helpSignal, &e1, &Elevator::callForHelp, Qt::QueuedConnection);
    //QObject::connect(&e1, &Elevator::callBuilding, &b, &Building::respondCall, Qt::QueuedConnection);

    ////QObject::connect(&w2, &MainWindow::openDoorSignal, &e2, &Elevator::openDoor, Qt::QueuedConnection);

    //w1.show();
    //w2.show();
    control.launch();
    return a.exec();
}
