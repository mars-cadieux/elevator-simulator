#include "elevatorui.h"
#include "elevator.h"


#include <QVBoxLayout>

ElevatorUI::ElevatorUI(QWidget *parent, Elevator* e)
    : QWidget{parent}
{
    owner = e;

    QVBoxLayout *layout = new QVBoxLayout(this);

    for(int i=1; i<=NUM_FLOORS; ++i){
        ElevatorButton *button = new ElevatorButton(i);
        elevatorButtons.push_back(button);
        layout->addWidget(button);

        //connect(button, SIGNAL(released()), this, SLOT (testFun()));
        connect(button, SIGNAL(released()), owner, SLOT (addStop()));
        //QObject::connect(&(*button), &ElevatorButton::pressed, &(*owner), &Elevator::addStop, Qt::QueuedConnection);
    }

    openDoorButton = new QPushButton("<|>");
    layout->addWidget(openDoorButton);
    QObject::connect(openDoorButton, SIGNAL(released()), owner, SLOT(openDoor()));

    closeDoorButton = new QPushButton(">|<");
    layout->addWidget(closeDoorButton);
    QObject::connect(closeDoorButton, SIGNAL(released()), owner, SLOT(closeDoor()));

    helpButton = new QPushButton("Help");
    layout->addWidget(helpButton);
    QObject::connect(helpButton, SIGNAL(released()), owner, SLOT(callForHelp()));
}

//ElevatorUI::ElevatorUI(Elevator* e){
//    owner = e;

//    QVBoxLayout *layout = new QVBoxLayout(this);

//    for(int i=1; i<=NUM_FLOORS; ++i){
//        ElevatorButton *button = new ElevatorButton(i);
//        elevatorButtons.push_back(button);
//        layout->addWidget(button);

//        //connect(button, SIGNAL(released()), this, SLOT (closeDoorButtonPressed()));
//        QObject::connect(&(*button), &ElevatorButton::pressed, &(*owner), &Elevator::addStop, Qt::QueuedConnection);
//    }
//}

ElevatorUI::~ElevatorUI()
{
    for(int i=0; i<elevatorButtons.size(); ++i){
        delete elevatorButtons[i];
    }
    elevatorButtons.clear();
}

void ElevatorUI::testFun()
{
    cout<<"test"<<endl;
}
