#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>

#include "door.h"
//#include "WeightSensor.h"
#include "doorsensor.h"
#include "building.h"
//#include "FloorSensor.h"
//#include "ElevatorUI.h"
//#include "ecs.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Elevator : public QObject {
    Q_OBJECT
    public:
        explicit Elevator(QObject* parent = nullptr); // Constructor
        ~Elevator(); // Destructor

        //getters and setters
        int getCurrentFloor() const;
        const string& getState() const;
        int getID() const;
        void setState(const string& state);
        int* getStops() const;
        Door* getDoor();

        //void attach(ECS* observer);
        //void detach(ECS* observer);

        void travel(const string& direction);	// initiates movement of the elevator in a particular direction and says 'while currentFloor != destinationFloor: keep moving'

        void updateFloor(int currentFloor); //updates currentFloor

        void addStop(int floor); //adds floor number to array of stops
        void removeStop(int floor); //removes stop from array of stops (used on arrival at floors and in emergency situations)

        void call911();

        void ringBell();
        void notify();

        bool obstructedStop();
        bool overloadStop();

    signals:
        void stop();
        //void callBuilding(int eID);
        void callBuilding(Elevator* e);

    public slots:
        void openDoor();
        void closeDoor();
        void callForHelp();
        //void call911(int eID);

    private:
        string state; //moving up, moving down, idle, stopped, boarding, overload stopped, obstructed stopped
        const int id;
        static int nextID;
        float weightLimit;
        int currentFloor;
        int* stops; //dynamic array with size equal to number of floors

        //ElevatorUI elevatorUI;
        Door* door;
        //WeightSensor weightSensor;
        DoorSensor* doorSensor;
       // FloorSensor floorSensor;
        Building* building; //pointer to the building that contains the elevator

        //ECS* observer;
};

#endif
