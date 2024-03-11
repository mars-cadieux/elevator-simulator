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

        friend class ECSThread;     //the allocation of requests function will operate on a separate thread since it is time consuming, this thread will need access to all of the ECS' private variables since it is doing the ECS' work

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
        void handleResults(QString s);      //receive and print the result of the ECS thread (will be a string indicating which elevator the request was allocated to

    private:
        vector<Elevator*> elevators;
        list<FloorRequest*> floorRequests;

        QTimer timer;

        void reset();       //reset the simulation to normal after an emergency. this function is private as no other class should be allowed to reset the simulation without the ECS' permission

};

#endif
