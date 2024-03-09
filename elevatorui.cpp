#include "elevatorui.h"
#include "elevator.h"

#include <cmath>

#include <QVBoxLayout>
#include <QGridLayout>

ElevatorUI::ElevatorUI(QWidget *parent, Elevator* e)
    : QWidget{parent}
{
    owner = e;

    //set the title of the window to the ID of its "owner" elevator
    QString eID = QString::number(owner->getID());
    QWidget::setWindowTitle("Elevator " + eID);

    //create new grid layout, and dynamically generate buttons and add them to this layout
    QGridLayout *layout = new QGridLayout(this);

    for(int i=1; i<=NUM_FLOORS; ++i){
        ElevatorButton *button = new ElevatorButton(i);
        elevatorButtons.push_back(button);
        //add buttons to widget in a grid with 3 columns
        layout->addWidget(button, std::floor((i-1)/3),  (i-1)%3);

        //connect(button, SIGNAL(released()), this, SLOT (testFun()));
        connect(button, SIGNAL(released()), owner, SLOT (addStop()));
    }

    //add the open door button, close door button, and help button onto the grid in a single row, starting after the final row of elevator buttons
    openDoorButton = new QPushButton("<|>");
    layout->addWidget(openDoorButton, std::ceil((NUM_FLOORS+3)/3), 0);
    QObject::connect(openDoorButton, SIGNAL(released()), owner, SLOT(openDoor()));

    closeDoorButton = new QPushButton(">|<");
    layout->addWidget(closeDoorButton, std::ceil((NUM_FLOORS+3)/3), 1);
    QObject::connect(closeDoorButton, SIGNAL(released()), owner, SLOT(closeDoor()));

    helpButton = new QPushButton("Help");
    layout->addWidget(helpButton, std::ceil((NUM_FLOORS+3)/3), 2);
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
