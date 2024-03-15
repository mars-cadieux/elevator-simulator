#include "floorbutton.h"

FloorButton::FloorButton(QWidget *parent, int fn, const string &d)
    : QPushButton{parent}, floorNum(fn), direction(d)
{
    state = "off";
    this->setText(direction == "up" ? "▲" : "▼");
    this->setFixedWidth(30);
    this->setStyleSheet("background-color: rgb(153, 224, 220)");
}

int FloorButton::getFloorNum() const
{
    return floorNum;
}

const string &FloorButton::getDirection() const
{
    return direction;
}

void FloorButton::illuminate()
{
    state = "on";
    setStyleSheet("background-color: rgb(255, 252, 163)");
}

void FloorButton::darken()
{
    state = "off";
    setStyleSheet("background-color: rgb(153, 224, 220)");
}
