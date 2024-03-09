#include "door.h"

Door::Door(int eID): elevatorID(eID), state("closed"){

}

void Door::open(){
    if(state != "open"){
        cout<<"Elevator "<<elevatorID<<" door opening. ";
    }
    setState("open");
}

void Door::close(){
    if(state != "closed"){
        cout<<"Elevator "<<elevatorID<<" door closing."<<endl;
    }
    setState("closed");
}

void Door::setState(const string &s)
{
    state = s;
}

const string &Door::getState() const
{
    return state;
}
