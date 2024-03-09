#include "ecs.h"

ECS::ECS(QObject *parent)
    : QObject{parent}
{

}

void ECS::addElevator(Elevator *e)
{
    elevators.push_back(e);
}

void ECS::powerOut()
{
    cout<<"Power outage. Starting backup  generator..."<<endl;
    for(int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergencyStop("There is a power outage in the building. Please disembark once we have reached a safe floor.");
    }
}

void ECS::fire()
{
    cout<<"Fire in building. Beginning emergency protocol..."<<endl;
    for(int i=0; i<elevators.size(); ++i){
        elevators[i]->removeAllStops();
        elevators[i]->emergencyStop("There is a fire in the building. Please disembark once we have reached a safe floor.");
    }
}

//this slot catches all signals emitted when an elevator closes its doors or when a stop is added
void ECS::checkStops()
{
    cout<<"ecs checking stops"<<endl;
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
                elevator->board();
            }
        }
    }
    else{
        elevator->setState("idle");
    }

}

//this slot catches all signals emitted when an elevator reachea a new floor
void ECS::checkFloor()
{
    cout<<"ecs checking floor"<<endl;
    Elevator* elevator = qobject_cast<Elevator*>(sender());

    int destFloor = elevator->getStops().front();

    if(destFloor>elevator->getCurrentFloor()){
        elevator->travel("up");
    }
    else if(destFloor<elevator->getCurrentFloor()){
        elevator->travel("down");
    }
    //if we are at the dest floor, stop and call board()
    else{
        elevator->board();
    }
}
