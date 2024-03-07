#include "elevator.h"

int Elevator::nextID = 0;

Elevator::Elevator(QObject *parent)
    : QObject{parent}, id(++nextID), currentFloor(1)
{
    door = new Door(id);
}

Elevator::~Elevator(){
    delete door;
}

int Elevator::getID() const{
    return id;
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

//void Elevator::callForHelp()
//{
//    cout<<"Calling building safety service..."<<endl;
//    emit callBuilding(id);
//}

void Elevator::callForHelp()
{
    cout<<"Calling building safety service..."<<endl;
    emit callBuilding(this);
}

void Elevator::call911()
{
       cout<<"No response from building. Placing 911 call."<<endl;
}
