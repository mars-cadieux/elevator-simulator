#include "building.h"
#include "elevator.h"

#include "defs.h"

#include <QTime>
#include <QCoreApplication>

Building::Building(QObject *parent)
    : QObject{parent}
{

}

void Building::respondCall(){
    Elevator* e = qobject_cast<Elevator*>(sender());
    if(BUILDING_RESPOND == 1){
        int eID = e->getID();
        cout<<"Building safety service connected to elevator "<<eID<<endl;
        bool response = e->helpPassenger();
        if(!response){
            call911();
        }
    }
    else{
        delay(5);
        e->call911();
    }
}

void Building::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void Building::call911()
{
    cout<<"No response from passenger. Placing 911 call."<<endl;
}
