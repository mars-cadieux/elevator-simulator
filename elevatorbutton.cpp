#include "elevatorbutton.h"

ElevatorButton::ElevatorButton(QPushButton *parent)
    : QPushButton{parent}
{

}

ElevatorButton::ElevatorButton(int floorNum)
{
    this->floorNum = floorNum;
    this->setText(QString::number(floorNum));
}

int ElevatorButton::getFloorNum()
{
    return floorNum;
}
