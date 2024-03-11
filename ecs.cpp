#include "ecs.h"

ECS::ECS(QObject *parent)
    : QObject{parent}
{
    //connect the 10 second timer to the reset function so that the simulation can go back to normal after an emergency scenario
    QObject::connect(&timer, &QTimer::timeout, this, &ECS::reset);
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
    qInfo("Power outage. Starting backup  generator...");
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergency("There is a power outage in the building. Please disembark once we have reached a safe floor.");
    }
    timer.start(10000);
    //cout<<"10 seconds until simulation returns to normal"<<endl;
}

void ECS::fire()
{
    qInfo("Fire in building. Beginning emergency protocol...");
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergency("There is a fire in the building. Please disembark once we have reached a safe floor.");
    }
    timer.start(10000);
    //cout<<"10 seconds until simulation returns to normal"<<endl;
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
                    elevator->board();
                }
            }
        }
    }
    else{
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
            //check to see if this stop is an elevvator completing a floor request
            std::list<FloorRequest*>::iterator end = floorRequests.end();
            for(std::list<FloorRequest*>::iterator it = floorRequests.begin(); it != end; ++it){
                if((*it)->eID == elevator->getID() && (*it)->floorNum == elevator->getCurrentFloor()){
                    emit requestCompleted((*it)->floorNum, (*it)->direction);
                    floorRequests.erase(it);
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
    emit requestReceived(floor, dir);

    ECSThread* ecsThread = new ECSThread(this, this, floor, dir);
    QObject::connect(ecsThread, &ECSThread::resultReady, this, &ECS::handleResults);
    QObject::connect(ecsThread, &ECSThread::finished, ecsThread, &QObject::deleteLater);
    ecsThread->start();

//    bool allocated = false;

//    //TODO: change to closest idle elevator
//    for(unsigned int i=0; i<elevators.size(); ++i){
//        //allocate the request to first idle elevator we find
//        if(elevators[i]->getState() == "idle"){
//            elevators[i]->addStopAsc(floor);
//            FloorRequest* newRequest = new FloorRequest(floor, dir, elevators[i]->getID());
//            floorRequests.push_back(newRequest);
//            allocated = true;
//            break;
//        }
//    }
//    //if we made it through the whole for loop and none of the elevators were idle, see if the floor making the request is on the same trajectory as one of the moving elevators
//    if(!allocated){
//        for(unsigned int i=0; i<elevators.size(); ++i){
//            //allocate the request to first idle elevator we find
//            if(elevators[i]->getState() == "travelling"){
//                if(elevators[i]->getTravelDirection() == "up" && floor > elevators[i]->getCurrentFloor()){
//                    elevators[i]->addStopAsc(floor);
//                    FloorRequest* newRequest = new FloorRequest(floor, dir, elevators[i]->getID());
//                    floorRequests.push_back(newRequest);
//                    allocated = true;
//                    break;
//                }
//                else if(elevators[i]->getTravelDirection() == "down" && floor < elevators[i]->getCurrentFloor()){
//                    elevators[i]->addStopDesc(floor);
//                    FloorRequest* newRequest = new FloorRequest(floor, dir, elevators[i]->getID());
//                    floorRequests.push_back(newRequest);
//                    allocated = true;
//                    break;
//                }
//            }
//        }
//    }
//    //if the request was still not able to be allocated, signal back that the request failed, and ask the floor button to make its request again
//    //we do this instead of using a while loop and just waiting until the request can be allocated so that the ECS isn't tied up by this while loop while other things are happening
//    if(!allocated){
//        emit requestFailed(floor, dir);
    //    }
}

void ECS::handleResults()
{
    qInfo("test");
}

void ECS::reset()
{
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->unblockAllSignals();
        elevators[i]->closeDoor();
        elevators[i]->setState("idle");
    }
    emit simulationReset();
}

void ECS::addRequest(FloorRequest *r)
{
    floorRequests.push_back(r);
}
