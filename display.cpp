#include "display.h"

Display::Display()
{

}

void Display::updateDisplay(const string& msg){
    this->currentMessage = msg;
}
