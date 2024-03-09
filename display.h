#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Elevator;

using namespace std;

class Display {
    public:
        Display(Elevator* e); //constructor
        ~Display(); //destructor

        void updateDisplay(const string& message);
        void updateDisplay(int floorNum);

    private:
        string currentMessage;
        Elevator* owner;
};

#endif
