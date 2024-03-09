#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Elevator;

using namespace std;

class AudioSystem {
    public:
        AudioSystem(Elevator* e); //constructor
        ~AudioSystem(); //destructor

        void setMessage(const string& msg);

    private:
        string currentMessage;
        Elevator* owner;        //pointer to the elevator that "owns" this audio system
};

#endif
