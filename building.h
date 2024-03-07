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
        void noResponse(int eID);

    public slots:
        //void respondCall(int eID);
        void respondCall(Elevator* e);

    private:
};

#endif // BUILDING_H
