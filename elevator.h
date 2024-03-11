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

class ElevatorUI;

using namespace std;

class Elevator : public QObject {
    Q_OBJECT
    public:
        explicit Elevator(QObject* parent = nullptr); // Constructor
        ~Elevator(); // Destructor


        //getters and setters
        int getCurrentFloor() const;
        const string& getState() const;
        const string& getTravelDirection() const;
        int getID() const;
        Door* getDoor() const;
        list<int> getStops() const;

        void setState(const string& state);


        //member functions
        void travel(const string& direction);	// initiates movement of the elevator in a particular direction and says 'while currentFloor != destinationFloor: keep moving'
        void updateFloor(int currentFloor); //updates currentFloor
        void removeAllStops(); //removes all stops in list, used in emergency situations
        void emergency(const string& msg);
        void emergencyStop();
        void showUI();  //calls show() on elevatorUI object, needed since controller does not have direct access to elevatorUI object
        void call911(); //places a 911 call if there is no response from building after callForHelp() is called
        void ringBell();
        //bool obstructedStop();
        //bool overloadStop();
        void board();
        void printStops();
        void addStopAsc(int f);     //add stop in ascending order. called by ECS when allocating floor requests, therefore not a slot
        void addStopDesc(int f);    //add stop in descending order. called by ECS when allocating floor requests, therefore not a slot

        friend class ECS;   //declare ECS a friend so ECS can call blockAllSignals(


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
        void addStop();

    private:
        const int id;
        static int nextID;
        string state;               //travelling, idle, boarding, emergency, overload stopped, obstructed stopped
        string travelDirection;     //up, down
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

        void delay(int seconds);       //function to add a 1 second delay between movement across floors, so the elevator doesn't travel at the speed of light
        void blockAllSignals();         //blocks all signals from elevator and its UI (buttons, etc). used in emergency scenarios
        void unblockAllSignals();       //unblocks all signals from elevator and its UI, called when the simulation goes back to normal

};

#endif
