#include "building.h"
#include "defs.h"
#include "elevator.h"

Building::Building(QObject *parent)
    : QObject{parent}
{

}

void Building::respondCall(Elevator* e){
    if(BUILDING_RESPOND){
        int eID = e->getID();
        cout<<"Building safety service connected to elevator "<<eID<<endl;
    }
    else{
        e->call911();
    }
}
