#include "audiosystem.h"
#include "elevator.h"

AudioSystem::AudioSystem(Elevator* e)
{
    owner = e;
}


void AudioSystem::setMessage(const string& msg){
    currentMessage = msg;
    int eID = owner->getID();
    cout<<"Elevator "<<eID<<" audio: "<<currentMessage<<endl;
}
