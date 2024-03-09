#ifndef ECS_H
#define ECS_H

#include <QObject>

//#include "FloorButton.h"
#include "elevator.h"
//#include "Building.h"

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class ECS :  public QObject{
    Q_OBJECT
    public:
        explicit ECS(QObject* parent = nullptr); // Constructor
        //~ECS(); // Destructor

        void takeRequest();
        void allocateRequest();		//Gives the request to the first elevator in the availableElevators vector. if the availableElevators vector is empty, check if any moving elevators can accommodate the request as a stop between their current floor and their destination
        void update();

        void addElevator(Elevator* e);
    signals:
    public slots:
        void powerOut();
        void fire();
    private:
        //vector<FloorButton*> floorButtons;
        vector<Elevator*> elevators;

        //vector<FloorButton*> floorRequests; 	//storing FloorButton pointers instead of making a FloorRequest object/class and storing those, since my FloorRequest object would just have a floorNum (int) and a direction (string), which the FloorButton already has.
        vector<Elevator*> availableElevators;
        //Building* building; //pointer to the building
};

#endif
