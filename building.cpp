#include "building.h"
#include "elevator.h"

#include "defs.h"

Building::Building(QObject *parent)
    : QObject{parent}
{

}

void Building::respondCall(){
    Elevator* e = qobject_cast<Elevator*>(sender());
    if(BUILDING_RESPOND == 1){
        int eID = e->getID();
        cout<<"Building safety service connected to elevator "<<eID<<endl;
    }
    else{
        e->call911();
    }
}
