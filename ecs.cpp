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
}

void ECS::fire()
{
    cout<<"Fire in building. Beginning emergency protocol..."<<endl;
}
