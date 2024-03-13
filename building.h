#ifndef BUILDING_H
#define BUILDING_H


#include <QObject>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Elevator;

using namespace std;

class Building : public QObject{
    Q_OBJECT
    public:
        explicit Building(QObject* parent = nullptr);

    signals:

    public slots:
        void respondCall();
        void call911();

    private:
        void delay(int seconds);    //adds a 5 second delay in the scenario where the building safety service does not respond
};

#endif // BUILDING_H
