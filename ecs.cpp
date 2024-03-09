#include "ecs.h"

ECS::ECS(QObject *parent)
    : QObject{parent}
{
    QObject::connect(&timer, &QTimer::timeout, this, &ECS::reset);
}

void ECS::addElevator(Elevator *e)
{
    elevators.push_back(e);
}

void ECS::powerOut()
{
    cout<<"Power outage. Starting backup  generator..."<<endl;
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergency("There is a power outage in the building. Please disembark once we have reached a safe floor.");
    }
    timer.start(10000);
    //cout<<"10 seconds until simulation returns to normal"<<endl;
}

void ECS::fire()
{
    cout<<"Fire in building. Beginning emergency protocol..."<<endl;
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
//this code looks very similar to checkStops(), and it is, but I couldn't just call checkStops() instead every time I reach a new floor because it was leading to doubled up calls of the function/slot
void ECS::checkFloor()
{
    //cout<<"ecs checking floor"<<endl;
    Elevator* elevator = qobject_cast<Elevator*>(sender());
    int eID = elevator->getID();


    int destFloor = elevator->getStops().front();

    //cout<<"elevator "<<eID<<"dest floor: "<<destFloor<<endl;

    if(destFloor>elevator->getCurrentFloor()){
        elevator->travel("up");
    }
    else if(destFloor<elevator->getCurrentFloor()){
        elevator->travel("down");
    }
    //if we are at the dest floor, stop and call board()
    else{
        if(elevator->getState() == "emergency"){
            elevator->emergencyStop();
        }
        else{
            elevator->board();
        }
    }
}

void ECS::reset()
{
    for(unsigned int i=0; i<elevators.size(); ++i){
        elevators[i]->unblockAllSignals();
        elevators[i]->closeDoor();
        elevators[i]->setState("idle");
    }
}
