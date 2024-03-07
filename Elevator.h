#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Door.h"
#include "Bell.h"
#include "WeightSensor.h"
#include "DoorSensor.h"
#include "FloorSensor.h"
#include "ElevatorUI.h"
#include "ECS.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Elevator {
    public:
        Elevator(); // Constructor
        ~Elevator(); // Destructor

        //getters and setters
        int getCurrentFloor() const;
        const string& getState() const;
        void setState(const string& state);
        int* getStops() const;
        Door* getDoor();

        void attach(ECS* observer);
        void detach(ECS* observer);

        void travel(const string& direction);	// initiates movement of the elevator in a particular direction and says 'while currentFloor != destinationFloor: keep moving'
        void stop();
        void updateFloor(int currentFloor); //updates currentFloor

        void addStop(int floor); //adds floor number to array of stops
        void removeStop(int floor); //removes stop from array of stops (used on arrival at floors and in emergency situations)

        void notify();

        bool obstructedStop(); //continously checks if there is an obstruction until the return p
        bool overloadStop();
    private:
        string state; //moving up, moving down, idle, stopped, boarding, overload stopped, obstructed stopped
        int id;
        float weightLimit;
        int currentFloor;
        int* stops; //dynamic array with size equal to number of floors

        ElevatorUI elevatorUI;
        Door door;
        Bell bell;
        WeightSensor weightSensor;
        DoorSensor doorSensor;
        FloorSensor floorSensor;

        ECS* observer;
};

#endif // ELEVATOR_H
