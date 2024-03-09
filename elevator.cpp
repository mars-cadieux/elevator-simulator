#include "elevator.h"

int Elevator::nextID = 0;

Elevator::Elevator(QObject *parent)
    : QObject{parent}, id(++nextID), currentFloor(1)
{
    door = new Door(id);
    elevatorUI = new ElevatorUI(nullptr, this);
    display = new Display(this);
    audioSystem = new AudioSystem(this);

    QObject::connect(&doorTimer, &QTimer::timeout, this, &Elevator::closeDoor);
}

Elevator::~Elevator(){
    delete door;
    delete elevatorUI;
    delete display;
    delete audioSystem;
}

int Elevator::getID() const{
    return id;
}

void Elevator::setState(const string &s)
{
    state = s;
}

void Elevator::travel(const string &direction)
{
    setState("travelling");
    int nextStop = stops.front();
    if(direction == "up"){
        while(currentFloor<nextStop){
            updateFloor(++currentFloor);
        }
    }
    else if(direction == "down"){
        while(currentFloor>nextStop){
            updateFloor(--currentFloor);
        }
    }
    board();
}

void Elevator::updateFloor(int cf)
{
    //cout<<"in updatefloor"<<endl;
    currentFloor = cf;
    display->updateDisplay(cf);
}


void Elevator::showUI()
{
    elevatorUI->show();
}

void Elevator::ringBell(){
    cout<<"Ding!"<<endl;
}

void Elevator::board()
{
    stops.pop_front();
    setState("boarding");
    ringBell();
    openDoor();
}

void Elevator::openDoor()
{
    if(state != "travelling"){
        //if the door is not open, open it and set timer for 10 seconds. if door is already open, reset timer to 10 seconds
        if(door->getState() != "open"){
            door->open();
        }
        doorTimer.start(10000);
        cout<<"10 seconds until door close."<<endl;
    }
    else{
        cout<<"Cannot open door while travelling."<<endl;
    }
}

void Elevator::closeDoor()
{
    if(door->getState() != "closed"){
        ringBell();
        door->close();
    }
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
    //cout<<"dest floor "<<floorNum<<endl;
    if(door->getState() == "open"){
        closeDoor();
    }
    stops.push_back(floorNum);

    if(stops.front()>currentFloor){
        travel("up");
    }
    else if(stops.front()< currentFloor){
        travel("down");
    }
    else{
        board();
    }
}


void Elevator::call911()
{
    cout<<"No response from building. Placing 911 call."<<endl;
}
