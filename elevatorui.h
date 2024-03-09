#ifndef ELEVATORUI_H
#define ELEVATORUI_H

#include "elevatorbutton.h"
#include "defs.h"

#include <QWidget>
#include <QPushButton>

class Elevator;

class ElevatorUI : public QWidget
{
    Q_OBJECT
public:
    explicit ElevatorUI(QWidget *parent = nullptr, Elevator* owner = nullptr);
    //ElevatorUI(Elevator* owner);
    ~ElevatorUI();

signals:

public slots:
    void testFun();

private:
    std::vector<ElevatorButton*> elevatorButtons;
    QPushButton* openDoorButton;
    QPushButton* closeDoorButton;
    QPushButton* helpButton;
    Elevator* owner;        //pointer to the elevator that "owns" this UI
};

#endif // ELEVATORUI_H
