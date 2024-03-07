#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Door {
    public:
        Door(int eid);

        void open();	//if not in fully opened position, move to fully opened position and set timer to be 10 seconds from current time. If in fully opened position, reset timer to be 10 seconds from current time
        void close();
    private:
        int elevatorID;
};

#endif
