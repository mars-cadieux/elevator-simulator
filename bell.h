#ifndef BELL_H
#define BELL_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Bell {
    public:
        void ring(); //Elevator object calls bell.ring() when it arrives at a floor to be serviced
};

#endif
