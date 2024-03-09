#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include <QTimer>

#include "door.h"
//#include "WeightSensor.h"
#include "doorsensor.h"
#include "building.h"
#include "display.h"
#include "audiosystem.h"
//#include "FloorSensor.h"
#include "elevatorui.h"
//#include "ecs.h"

#include <iostream>
#include <string>
#include <vector>
#include <list>

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
        list<int> getStops() const;
        Door* getDoor() const;

        //void attach(ECS* observer);
        //void detach(ECS* observer);

        void travel(const string& direction);	// initiates movement of the elevator in a particular direction and says 'while currentFloor != destinationFloor: keep moving'

        void updateFloor(int currentFloor); //updates currentFloor


        void removeAllStops(); //removes all stops in list, used in emergency situations
        void emergencyStop(const string& msg);

        void showUI();

        void call911();

        void ringBell();
        void notify();

        bool obstructedStop();
        bool overloadStop();

        void board();



    signals:
        void stop();
        //void callBuilding(int eID);
        void callBuilding();
        void doorClosed();
        void stopAdded();
        void newFloor();

    public slots:
        void openDoor();
        void closeDoor();
        void callForHelp();
        //void call911(int eID);
        //void addStop();
        void addStop(); //adds floor number to array of stops



    private:
        const int id;
        static int nextID;
        string state; //moving up, moving down, idle, stopped, boarding, overload stopped, obstructed stopped
        float weightLimit;
        int currentFloor;
        std::list<int> stops;

        ElevatorUI* elevatorUI;
        Door* door;
        Display* display;
        AudioSystem* audioSystem;
        //WeightSensor weightSensor;
        DoorSensor* doorSensor;
        //FloorSensor floorSensor;
        Building* building; //pointer to the building that contains the elevator

        QTimer doorTimer;   //timer to close the door after 10 seconds

        void delay();       //fucntion to add a 1 second delay between movement across floors, so the elevator doesn't travel at the speed of light

        //ECS* observer;
};

#endif
