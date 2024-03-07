#include "door.h"

Door::Door(int eID): elevatorID(eID){}

void Door::open(){
    cout<<"Elevator "<<elevatorID<<" door opening"<<endl;

    //TODO: QElapsedTimer for 10 sec delay then close door
}

void Door::close(){
    cout<<"Elevator "<<elevatorID<<" door closing"<<endl;
}
