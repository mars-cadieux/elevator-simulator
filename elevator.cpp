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
    stops.clear();
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

//adds a 1 second delay between floor movement so the simulation is a bit more realistic
void Elevator::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Elevator::blockAllSignals()
{
    this->blockSignals(true);
    elevatorUI->blockAllSignals();
}

void Elevator::unblockAllSignals()
{
    this->blockSignals(false);
    elevatorUI->unblockAllSignals();
}

void Elevator::travel(const string &direction)
{

   if(door->getState() == "open"){
       qInfo("Cannot travel while door is open.");
   }
   else{
       setState("travelling");
       if(direction == "up"){
           travelDirection = "up";
           delay(1);
           updateFloor(++currentFloor);
           emit newFloor();
       }
       else if(direction == "down"){
           travelDirection = "down";
           delay(1);
           updateFloor(--currentFloor);
           emit newFloor();
       }
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

void Elevator::emergency(const string &msg)
{
    //this->blockSignals(true);
    display->updateDisplay(msg);
    audioSystem->setMessage(msg);

    //stops.push_back(currentFloor);

    //
    //stops.pop_front();
    //delay();

    if(state == "travelling"){
        if(travelDirection == "up"){
            stops.push_back(currentFloor+1);
        }
        else if(travelDirection == "down"){
            stops.push_back(currentFloor-1);
        }
    }
    else{
        stops.push_back(currentFloor);
        emit stopAdded();
    }
    setState("emergency");

//
}

void Elevator::emergencyStop()
{
    stops.pop_front();
    setState("emergency stopped");
    travelDirection = "";
    ringBell();
    display->updateDisplay("Safe floor reached. Please disembark.");
    audioSystem->setMessage("We have reached the safe floor. Please disembark as soon as possible.");
    door->open();

    //pause the elevator for 10 seconds, then return the simulation back to normal
    blockAllSignals();
    cout<<"10 seconds until simulation returns to normal"<<endl;
    //the ECS starts the 10 second timer
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
    travelDirection = "";
    ringBell();
    openDoor();
}

//used for debugging
void Elevator::printStops()
{
    string stopsString = "Elevator " + to_string(id) + " stops: ";

    std::list<int>::iterator end = stops.end();
    for(std::list<int>::iterator it = stops.begin(); it != end; ++it){
        stopsString += to_string(*it);
        stopsString += ", ";
    }
    cout<<stopsString<<endl;
}

void Elevator::addStopAsc(int f)
{
    if(stops.size() > 0){
        std::list<int>::iterator end = stops.end();
        for(std::list<int>::iterator it = stops.begin(); it != end; ++it){
            if(f < *it){
                stops.insert(it, f);
            }
        }
    }
    else{
        stops.push_back(f);
    }
}

void Elevator::addStopDesc(int f)
{
    if(stops.size() > 0){
        std::list<int>::iterator end = stops.end();
        for(std::list<int>::iterator it = stops.begin(); it != end; ++it){
            if(f > *it){
                stops.insert(it, f);
            }
        }
    }
    else{
        stops.push_back(f);
    }
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

//TODO: set state, pause elevator, resume after 10 secoondss
void Elevator::callForHelp()
{
    cout<<"Calling building safety service..."<<endl;
    emit callBuilding();
}

//this slot catches signals emitted when an elevator button is pressed
void Elevator::addStop()
{
    ElevatorButton* eButton = qobject_cast<ElevatorButton*>(sender());
    int floorNum = eButton->getFloorNum();

    //TODO: unsure if adding a stop should close the door and start the travel process, the way I have things rn makes things easier, get rid of this if I have time
    if(door->getState() == "open"){
        closeDoor();
    }

    //if the elevator already has some stops, we might need too add the new stop in sorted order
    if(stops.size() > 0){
        std::list<int>::iterator end = stops.end();
        //if a stop has been added while the elevator is moving up, and the stop is above the current floor, add that stop in sorted order
        if(state == "travelling" && travelDirection == "up" && floorNum > currentFloor){
            for(std::list<int>::iterator it = stops.begin(); it != end; ++it){
                if(floorNum < *it){
                    stops.insert(it, floorNum);
                }
            }
        }
        //same thing but for whenn a stop is added while the elevator is moving down, and the stop is below the current floor
        else if(state == "travelling" && travelDirection == "down" && floorNum < currentFloor){
            for(std::list<int>::iterator it = stops.begin(); it != end; ++it){
                if(floorNum > *it){
                    stops.insert(it, floorNum);
                }
            }
        }
        //if the new stop is not on the elevator's current trajectory, add it to the end
        else{
            stops.push_back(floorNum);
        }
    }
    //if the elevator has no current stops add the new stop to the end
    else{
        stops.push_back(floorNum);
    }
    printStops();   //TOODO: used for debugging, delete later
    emit stopAdded();
}




void Elevator::call911()
{
    cout<<"No response from building. Placing 911 call."<<endl;
}
