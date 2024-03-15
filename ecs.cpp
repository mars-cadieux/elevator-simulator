#include "ecs.h"

ECS::ECS(QObject *parent)
    : QObject{parent}
{



}

ECS::~ECS()
{
    std::list<FloorRequest*>::iterator end = floorRequests.end();
    for(std::list<FloorRequest*>::iterator it = floorRequests.begin(); it != end; ++it){
        delete *it;
    }
    floorRequests.clear();
}

void ECS::addElevator(Elevator *e)
{
    elevators.push_back(e);
}

void ECS::powerOut()
{
    timer = new QTimer(this);
    //connect the 10 second timer to the reset function so that the simulation can go back to normal after an emergency scenario
    QObject::connect(timer, &QTimer::timeout, this, &ECS::reset);

    qInfo("Power outage. Starting backup  generator...");
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergency("Power outage in building. \nMoving to safe floor.");
    }
    //delete all floor requests
    while(floorRequests.size()>0){
        FloorRequest* yeet = floorRequests.back();
        floorRequests.pop_back();
        delete yeet;
    }
    //start a timer to pause the simulation for 10 seconds
    timer->start(10000);
}

void ECS::fire()
{   
    timer = new QTimer(this);
    //connect the 10 second timer to the reset function so that the simulation can go back to normal after an emergency scenario
    QObject::connect(timer, &QTimer::timeout, this, &ECS::reset);

    qInfo("Fire in building. Beginning emergency protocol...");
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergency("Fire in the building. \nMoving to safe floor.");
    }
    //delete all floor requests
    while(floorRequests.size()>0){
        FloorRequest* yeet = floorRequests.back();
        floorRequests.pop_back();
        delete yeet;
    }
    //start a timer to pause the simulation for 10 seconds
    timer->start(10000);
}

void ECS::elevatorFire()
{
    QTimer* singleTimer = new QTimer(this);
    singleTimers.push_back(singleTimer);
    QObject::connect(singleTimer, &QTimer::timeout, this, &ECS::resetSingleElevator);

    Elevator* elevator = qobject_cast<Elevator*>(sender());
    string eID = to_string(elevator->getID());
    string msg = "Fire in elevator " + eID + ". Beginning emergency protocol...";
    qInfo(msg.c_str());
    elevator->removeAllStops();
    elevator->emergency("Fire detected. \nMoving to safe floor.");

    //start a timer to pause the simulation for 10 seconds
    singleTimer->start(10000);
}

void ECS::elevatorEmergency()
{
    QTimer* singleTimer = new QTimer(this);
    singleTimers.push_back(singleTimer);
    QObject::connect(singleTimer, &QTimer::timeout, this, &ECS::resetSingleElevator);

    Elevator* elevator = qobject_cast<Elevator*>(sender());
    string eID = to_string(elevator->getID());
    string msg = "Elevator " + eID + " has called for help.";
    qInfo(msg.c_str());
    elevator->removeAllStops();
//    if(elevator->state == "travelling"){
//        if(elevator->travelDirection == "up"){
//            elevator->stops.push_back(elevator->currentFloor+1);
//        }
//        else if(elevator->travelDirection == "down"){
//            elevator->stops.push_back(elevator->currentFloor-1);
//        }
//    }
//    else{
//        elevator->stops.push_back(elevator->currentFloor);
//    }
    elevator->setState("emergency stopped");
    elevator->blockAllSignals();
    string msg2 = "Elevator " + eID + " has been stopped.  10  seconds  until elevator " + eID + " returns to normal.";
    qInfo(msg2.c_str());

    //start a timer to pause the simulation for 10 seconds
    singleTimer->start(10000);
}

//this slot catches all signals emitted when an elevator closes its doors or when a stop is added
void ECS::checkStops()
{
    //cout<<"ecs checking stops"<<endl;
    Elevator* elevator = qobject_cast<Elevator*>(sender());

    //if stops are non-empty, we want to call travel() on our elevator. otherwise, our elevator has finished its last stop and we set its state to idle
    if((elevator->getStops().size() > 0)){
        if(elevator->getState() != "travelling"){
            if((elevator->getStops()).front()>elevator->getCurrentFloor()){
                elevator->travel("up");
            }
            else if((elevator->getStops()).front()<elevator->getCurrentFloor()){
                elevator->travel("down");
            }
            //if someone has added a stop at the floor they are currently on, (ex.  pressed the dest floor 2 button while the elevator is at floor 2), simply call board()
            else{
                if(elevator->getState() == "emergency"){
                    elevator->emergencyStop();
                }
                else{
                    //check to see if this stop is an elevator completing a floor request
                    std::list<FloorRequest*>::iterator end = floorRequests.end();
                    for(std::list<FloorRequest*>::iterator it = floorRequests.begin(); it != end; ++it){
                        if((*it)->eID == elevator->getID() && (*it)->floorNum == elevator->getCurrentFloor()){
                            emit requestCompleted((*it)->floorNum, (*it)->direction);
                            FloorRequest* yeet = *it;
                            floorRequests.erase(it);
                            delete yeet;
                            break;
                        }
                    }
                    elevator->board();
                }
            }
        }
    }
    else if(elevator->getState() != "emergency stopped"){
        elevator->setState("idle");
    }
}

//this slot catches all signals emitted when an elevator reaches a new floor
//this code looks very similar to checkStops(), and it is, but I couldn't just call checkStops() instead every time I reach a new floor because it was leading to doubled up calls of travel()
void ECS::checkFloor()
{
    //cout<<"ecs checking floor"<<endl;
    Elevator* elevator = qobject_cast<Elevator*>(sender());
    int destFloor = elevator->getStops().front();

    if(destFloor>elevator->getCurrentFloor()){
        elevator->travel("up");
    }
    else if(destFloor<elevator->getCurrentFloor()){
        elevator->travel("down");
    }
    //if we are at the dest floor, stop and call board() or emergencyStop() if it's an emergency
    else{
        if(elevator->getState() == "emergency"){
            elevator->emergencyStop();
        }
        else{
            //check to see if this stop is an elevator completing a floor request
            std::list<FloorRequest*>::iterator end = floorRequests.end();
            for(std::list<FloorRequest*>::iterator it = floorRequests.begin(); it != end; ++it){
                if((*it)->eID == elevator->getID() && (*it)->floorNum == elevator->getCurrentFloor()){
                    emit requestCompleted((*it)->floorNum, (*it)->direction);
                    FloorRequest* yeet = *it;
                    floorRequests.erase(it);
                    delete yeet;
                    break;
                }
            }
            elevator->board();
        }
    }
}

void ECS::receiveRequest(int floor, const string &dir)
{
    cout<<"floor "<<floor<<" "<<dir<<" requested"<<endl;
    //this signal tells the floor button to illuminate
    emit requestReceived(floor, dir);

    //make a new thread and offload the work of this function to said thread
    ECSThread* ecsThread = new ECSThread(this, this, floor, dir);
    QObject::connect(ecsThread, &ECSThread::resultReady, this, &ECS::handleResults);
    QObject::connect(ecsThread, &ECSThread::finished, ecsThread, &QObject::deleteLater);
    ecsThread->start();
}

//print the result of the ecs thread, will be a string indicating which elevator the request was allocated to
void ECS::handleResults(QString s)
{
    cout<<s.toStdString()<<endl;
}

void ECS::reset()
{
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->unblockAllSignals();
        elevators[i]->closeDoor();
        elevators[i]->setState("idle");
        elevators[i]->display->updateDisplay(elevators[i]->currentFloor);
    }
    delete timer;
    emit simulationReset();
}

void ECS::resetSingleElevator()
{
    for(unsigned int i=0; i<elevators.size(); ++i){
        if(elevators[i]->getState() == "emergency stopped"){
            elevators[i]->unblockAllSignals();
            elevators[i]->closeDoor();
            elevators[i]->setState("idle");
            elevators[i]->display->updateDisplay(elevators[i]->currentFloor);
            break;
        }
    }
    QTimer* yeet = singleTimers.front();
    singleTimers.pop_front();
    delete yeet;
}
