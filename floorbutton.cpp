#include "floorbutton.h"

FloorButton::FloorButton(QWidget *parent, int fn, const string &d)
    : QPushButton{parent}, floorNum(fn), direction(d)
{
    this->setText(direction == "up" ? "▲" : "▼");
}

int FloorButton::getFloorNum() const
{
    return floorNum;
}

const string &FloorButton::getDirection() const
{
    return direction;
}
