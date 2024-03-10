#include "controller.h"
#include "defs.h"
#include "elevatorbutton.h"
#include "elevatorui.h"
#include "floorbutton.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

Controller::~Controller()
{
    for(unsigned int i=0; i<elevators.size(); ++i){
        delete elevators[i];
    }
    elevators.clear();
}

void Controller::launch()
{

    //generate all elevators, add their pointers to the ECS, and connect all slots and signals
    for(int i=0; i<NUM_ELEVATORS; ++i){
        Elevator* e = new Elevator();
        elevators.push_back(e);
        ecs.addElevator(e);
        e->showUI();

        QObject::connect(&(*elevators[i]), &Elevator::callBuilding, &b, &Building::respondCall, Qt::QueuedConnection);
        QObject::connect(&(*elevators[i]), &Elevator::doorClosed, &ecs, &ECS::checkStops, Qt::QueuedConnection);
        QObject::connect(&(*elevators[i]), &Elevator::stopAdded, &ecs, &ECS::checkStops, Qt::QueuedConnection);
        QObject::connect(&(*elevators[i]), &Elevator::newFloor, &ecs, &ECS::checkFloor, Qt::QueuedConnection);
    }

    //connect the slots and signals for the emergency procedures
    QObject::connect(&w, &MainWindow::powerOut, &ecs, &ECS::powerOut, Qt::QueuedConnection);
    QObject::connect(&w, &MainWindow::fire, &ecs, &ECS::fire, Qt::QueuedConnection);
    QObject::connect(&ecs, &ECS::simulationReset, &w, &MainWindow::resume, Qt::QueuedConnection);

    //connect the slots and signals for everything related to floor requests
    QObject::connect(&w, &MainWindow::floorButtonPressed, &ecs, &ECS::receiveRequest);

    w.show();
}
