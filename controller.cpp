#include "controller.h"
#include "defs.h"
#include "elevatorbutton.h"
#include "elevatorui.h"

#include <QWidget>
#include <QVBoxLayout>

Controller::Controller(QObject *parent)
    : QObject{parent}
{

}

Controller::~Controller()
{
    for(int i=0; i<elevators.size(); ++i){
        delete elevators[i];
    }
    elevators.clear();

    for(int i=0; i<elevatorUIs.size(); ++i){
        delete elevatorUIs[i];
    }
    elevatorUIs.clear();
}

void Controller::launch()
{

    for(int i=0; i<NUM_ELEVATORS; ++i){
        Elevator* e = new Elevator();
        elevators.push_back(e);
        ecs.addElevator(e);
        e->showUI();



        //QWidget *window = new QWidget;


        //elevatorUIs.push_back(elevatorUI);



//        ElevatorButton *button1 = new ElevatorButton(1);
//        //button1->setText(QString::number(1));
//        QPushButton *button2 = new QPushButton("Two");
//        QPushButton *button3 = new QPushButton("Three");
//        QPushButton *button4 = new QPushButton("Four");
//        QPushButton *button5 = new QPushButton("Five");

//        QVBoxLayout *layout = new QVBoxLayout(window);
//        layout->addWidget(button1);
//        layout->addWidget(button2);
//        layout->addWidget(button3);
//        layout->addWidget(button4);
//        layout->addWidget(button5);


        //elevatorUI->show();
        QObject::connect(&(*elevators[i]), &Elevator::callBuilding, &b, &Building::respondCall, Qt::QueuedConnection);
    }

//    for(int i=0; i<elevators.size(); ++i){
//        QObject::connect(&(*windows[i]), &MainWindow::openDoorSignal, &(*elevators[i]), &Elevator::openDoor, Qt::QueuedConnection);
//        QObject::connect(&(*windows[i]), &MainWindow::closeDoorSignal, &(*elevators[i]), &Elevator::closeDoor, Qt::QueuedConnection);
//        QObject::connect(&(*windows[i]), &MainWindow::helpSignal, &(*elevators[i]), &Elevator::callForHelp, Qt::QueuedConnection);
//        QObject::connect(&(*elevators[i]), &Elevator::callBuilding, &b, &Building::respondCall, Qt::QueuedConnection);
//        //QObject::connect(&b, &Building::noResponse, &(*elevators[i]), &Elevator::call911, Qt::QueuedConnection);

//        windows[i]->show();
//    }

    QObject::connect(&w, &MainWindow::powerOut, &ecs, &ECS::powerOut, Qt::QueuedConnection);
    QObject::connect(&w, &MainWindow::fire, &ecs, &ECS::fire, Qt::QueuedConnection);

    w.show();
}
