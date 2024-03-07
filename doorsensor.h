#ifndef DOORSENSOR_H
#define DOORSENSOR_H


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class DoorSensor {
    public:
        DoorSensor(); // Constructor
        ~DoorSensor(); // Destructor

        bool detectDoor(); //detect if the door is obstructed, update obstructed and return it

    private:
        bool obstructed;
        int elevatorID; //ID of elevator that this sensor belongs to
};

#endif
