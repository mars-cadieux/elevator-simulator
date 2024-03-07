#include "controller.h"
#include "defs.h"

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    for(int i=0; i<NUM_ELEVATORS; ++i){
        Elevator* e = new Elevator();
        elevators.push_back(e);

        MainWindow* w = new MainWindow();
        windows.push_back(w);
    }
}

Controller::~Controller()
{
    for(int i=0; i<elevators.size(); ++i){
        delete elevators[i];
    }
    elevators.clear();

    for(int i=0; i<windows.size(); ++i){
        delete windows[i];
    }
    windows.clear();
}

void Controller::launch()
{
    for(int i=0; i<elevators.size(); ++i){
        QObject::connect(&(*windows[i]), &MainWindow::openDoorSignal, &(*elevators[i]), &Elevator::openDoor, Qt::QueuedConnection);
        QObject::connect(&(*windows[i]), &MainWindow::closeDoorSignal, &(*elevators[i]), &Elevator::closeDoor, Qt::QueuedConnection);
        QObject::connect(&(*windows[i]), &MainWindow::helpSignal, &(*elevators[i]), &Elevator::callForHelp, Qt::QueuedConnection);
        QObject::connect(&(*elevators[i]), &Elevator::callBuilding, &b, &Building::respondCall, Qt::QueuedConnection);
        //QObject::connect(&b, &Building::noResponse, &(*elevators[i]), &Elevator::call911, Qt::QueuedConnection);

        windows[i]->show();
    }
}
