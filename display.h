#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <QObject>

class Elevator;

using namespace std;

class Display : public QObject{
    Q_OBJECT
    public:
        explicit Display(QObject* parent = nullptr, Elevator* e = nullptr); //constructor
        ~Display(); //destructor

        const string& getMessage() const;

        void updateDisplay(const string& message);
        void updateDisplay(int floorNum);
    signals:
        void displayUpdated();
    private:
        string currentMessage;
        Elevator* owner;
};

#endif
