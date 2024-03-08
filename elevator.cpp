#include "elevator.h"

int Elevator::nextID = 0;

Elevator::Elevator(QObject *parent)
    : QObject{parent}, id(++nextID), currentFloor(1)
{
    door = new Door(id);
    elevatorUI = new ElevatorUI(nullptr, this);
}

Elevator::~Elevator(){
    delete door;
    delete elevatorUI;
}

int Elevator::getID() const{
    return id;
}

void Elevator::showUI()
{
    elevatorUI->show();
}

void Elevator::ringBell(){
    cout<<"Ding!"<<endl;
}

void Elevator::openDoor()
{
    door->open();
}

void Elevator::closeDoor()
{
    ringBell();
    door->close();
}


void Elevator::callForHelp()
{
    cout<<"Calling building safety service..."<<endl;
    emit callBuilding();
}


void Elevator::addStop()
{
    ElevatorButton* eButton = qobject_cast<ElevatorButton*>(sender());
    int floorNum = eButton->getFloorNum();
    cout<<"dest floor "<<floorNum<<endl;
}


void Elevator::call911()
{
    cout<<"No response from building. Placing 911 call."<<endl;
}
