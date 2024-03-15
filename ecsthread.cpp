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
    while(!allocated){
        for(unsigned int i=0; i<ecs->elevators.size(); ++i){
            //allocate the request to first idle elevator we find
            if(ecs->elevators[i]->getState() == "idle"){
                ecs->elevators[i]->addStopAsc(floor);
                FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
                ecs->floorRequests.push_back(newRequest);

                string msg = "Floor " + to_string(floor) + " " + dir + " request allocated to elevator " + to_string(ecs->elevators[i]->getID());
                result = QString::fromStdString(msg);

                allocated = true;
                break;
            }
        }
        //if we made it through the whole for loop and none of the elevators were idle, see if the floor making the request is on the same trajectory as one of the moving elevators
        if(!allocated){
            for(unsigned int i=0; i<ecs->elevators.size(); ++i){
                //if our elevator is travelling up and the request is at least 2 floors higher than current floor, elevator is a candidate for allocation
                //we go up at least 2 floors instead of at least 1 floor so we don't risk allocating the request to the elevator immediately after it passes that floor
                // (idk if I explained that well but there's weirdness caused by the delay between floors that can lead to requests gettinng allocated then skipped)
                if(ecs->elevators[i]->getState() == "travelling"){
                    if(ecs->elevators[i]->getTravelDirection() == "up" && floor > ecs->elevators[i]->getCurrentFloor() + 1){
                        //if floor request is to go up and floor is less than elevator's final stop, it can take this request
                        if(ecs->elevators[i]->getStops().size() > 0  && ecs->elevators[i]->getStops().back() > floor && dir == "up"){
                            ecs->elevators[i]->addStopAsc(floor);
                            FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
                            ecs->floorRequests.push_back(newRequest);

                            string msg = "Floor " + to_string(floor) + " " + dir + " request allocated to elevator " + to_string(ecs->elevators[i]->getID());
                            result = QString::fromStdString(msg);

                            allocated = true;
                            break;
                        }
                    }
                    //if our elevator is travelling down and the request is at least 2 floors lower than current floor, elevator is a candidate for allocation
                    else if(ecs->elevators[i]->getTravelDirection() == "down" && floor < ecs->elevators[i]->getCurrentFloor() - 1){
                        //if floor request is to go down and floor is greater than elevator's final stop, it can take this request
                        if(ecs->elevators[i]->getStops().size() > 0 && ecs->elevators[i]->getStops().back() < floor && dir == "down"){
                            ecs->elevators[i]->addStopDesc(floor);
                            FloorRequest* newRequest = new FloorRequest(floor, dir, ecs->elevators[i]->getID());
                            ecs->floorRequests.push_back(newRequest);

                            string msg = "Floor " + to_string(floor) + " " + dir + " request allocated to elevator " + to_string(ecs->elevators[i]->getID());
                            result = QString::fromStdString(msg);

                            allocated = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    emit resultReady(result);
}
