#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class AudioSystem {
    public:
        AudioSystem(); //constructor
        ~AudioSystem(); //destructor

        void setMessage(const string& msg);

    private:
        string currentMessage;
};

#endif
