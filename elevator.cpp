#include "elevator.h"

#include <QTime>
#include <QCoreApplication>

int Elevator::nextID = 0;

Elevator::Elevator(QObject *parent)
    : QObject{parent}, id(++nextID), state("idle"), weightLimit(250.00), currentFloor(1)
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

int Elevator::getCurrentFloor() const
{
    return currentFloor;
}

const string &Elevator::getState() const
{
    return state;
}

int Elevator::getID() const{
    return id;
}

void Elevator::setState(const string &s)
{
    state = s;
}

list<int> Elevator::getStops() const
{
    return stops;
}

Door *Elevator::getDoor() const
{
    return door;
}

//adds a 1 second delay between floor movement so simulation is a bit more realistic
void Elevator::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Elevator::travel(const string &direction)
{
    setState("travelling");
    if(direction == "up"){
        delay();
        updateFloor(++currentFloor);
        emit newFloor();
    }
    else if(direction == "down"){
        delay();
        updateFloor(--currentFloor);
        emit newFloor();
    }
}

void Elevator::updateFloor(int cf)
{
    currentFloor = cf;
    display->updateDisplay(cf);
}

void Elevator::removeAllStops()
{
    while(stops.size()>0){
        stops.pop_front();
    }
}

void Elevator::emergencyStop(const string &msg)
{
    display->updateDisplay(msg);
    audioSystem->setMessage(msg);
}


void Elevator::showUI()
{
    elevatorUI->show();
}

void Elevator::ringBell()
{
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
        emit doorClosed();
    }
}


void Elevator::callForHelp()
{
    cout<<"Calling building safety service..."<<endl;
    emit callBuilding();
}

//this slot catches signals emitted when an elevatorr button is pressed
void Elevator::addStop()
{
    ElevatorButton* eButton = qobject_cast<ElevatorButton*>(sender());
    int floorNum = eButton->getFloorNum();

    //TODO: unsure if adding a stop should close the door and start the travel process, the way I have things rn makes things easier, get rid of this if I have time
    if(door->getState() == "open"){
        closeDoor();
    }
    stops.push_back(floorNum);
    emit stopAdded();
}




void Elevator::call911()
{
    cout<<"No response from building. Placing 911 call."<<endl;
}
