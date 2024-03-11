#ifndef ECS_H
#define ECS_H

#include <QObject>
#include <QTimer>
#include <QThread>

//#include "FloorButton.h"
#include "elevator.h"
#include "floorrequest.h"
#include "ecsthread.h"
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
        ~ECS(); // Destructor

//        class FloorRequest{
//            public:
//                FloorRequest(int f, const string& dir, int id): floorNum(f), direction(dir), eID(id) {};
//                int floorNum;
//                string direction;
//                int eID;    //id of the elevator that is taking the request
//        };

        friend class ECSThread;

        //void takeRequest();
        void allocateRequest();		//Gives the request to the first elevator in the availableElevators vector. if the availableElevators vector is empty, check if any moving elevators can accommodate the request as a stop between their current floor and their destination
        void update();

        void addElevator(Elevator* e);

    signals:
        void simulationReset();     //communicates to main window that the simulation has been reset, so the main window can unblock all its signals
        void requestReceived(int f, const string& dir);
        void requestCompleted(int f, const string& dir);
        void requestFailed(int f, const string& dir);

    public slots:
        void powerOut();
        void fire();
        void checkStops();
        void checkFloor();
        void receiveRequest(int floor, const string& dir);
        void handleResults();

    private:
        //vector<FloorButton*> floorButtons;
        vector<Elevator*> elevators;
        list<FloorRequest*> floorRequests;

        //vector<FloorButton*> floorRequests; 	//storing FloorButton pointers instead of making a FloorRequest object/class and storing those, since my FloorRequest object would just have a floorNum (int) and a direction (string), which the FloorButton already has.
        //vector<Elevator*> availableElevators;
        QTimer timer;

        void reset();       //reset the simulation to normal after an emergency. this function is private as no other class should be allowed to reset the simulation without the ECS' permission
        //Building* building; //pointer to the building
        void addRequest(FloorRequest* r);
};

#endif
