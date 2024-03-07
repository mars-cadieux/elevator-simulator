#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Display {
    public:
        Display(); //constructor
        ~Display(); //destructor

        void updateDisplay(const string& message);

    private:
        string currentMessage;
};

#endif
