#include "ecsthread.h"
#include "ecs.h"
#include "floorrequest.h"

ECSThread::ECSThread(QObject *parent, ECS* e, int f, const std::string&d)
    : QThread{parent}, floor(f), dir(d)
{
    ecs = e;
}

void ECSThread::run()
{
    QString result;

    bool allocated = false;

    //TODO: change to closest idle elevator
    for(unsigned int i=0; i<ecs->elevators.size(); ++i){
        //allocate the request to first idle elevator we find
        if(ecs->elevators[i]->getState() == "idle"){
            ecs->elevators[i]->addStopAsc(floor);
            FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
            ecs->addRequest(newRequest);
            allocated = true;
            break;
        }
    }
    //if we made it through the whole for loop and none of the elevators were idle, see if the floor making the request is on the same trajectory as one of the moving elevators
    if(!allocated){
        for(unsigned int i=0; i<ecs->elevators.size(); ++i){
            //allocate the request to first idle elevator we find
            if(ecs->elevators[i]->getState() == "travelling"){
                if(ecs->elevators[i]->getTravelDirection() == "up" && floor > ecs->elevators[i]->getCurrentFloor()){
                    ecs->elevators[i]->addStopAsc(floor);
                    FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
                    ecs->floorRequests.push_back(newRequest);
                    allocated = true;
                    break;
                }
                else if(ecs->elevators[i]->getTravelDirection() == "down" && floor < ecs->elevators[i]->getCurrentFloor()){
                    ecs->elevators[i]->addStopDesc(floor);
                    FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
                    ecs->floorRequests.push_back(newRequest);
                    allocated = true;
                    break;
                }
            }
        }
    }
    //if the request was still not able to be allocated, signal back that the request failed, and ask the floor button to make its request again
    //we do this instead of using a while loop and just waiting until the request can be allocated so that the ECS isn't tied up by this while loop while other things are happening
    result = QString("test");

    emit resultReady(result);
}
