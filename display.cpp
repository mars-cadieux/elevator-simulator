#include "display.h"
#include "elevator.h"

Display::Display(Elevator* e)
{
    owner = e;
}

void Display::updateDisplay(const string& msg){
    currentMessage = msg;
    int eID = owner->getID();
    cout<<"Elevator "<<eID<<" display: "<<currentMessage<<endl;
}

void Display::updateDisplay(int floorNum){

    string sFloorNum = to_string(floorNum);
    string msg = "Floor " + sFloorNum;

    currentMessage = msg;
    int eID = owner->getID();
    //cout<<"in updateDisplay"<<endl;
    cout<<"Elevator "<<eID<<" display: "<<currentMessage<<endl;
}
