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

    friend class Elevator;

signals:

public slots:
    void testFun();

private:
    std::vector<ElevatorButton*> elevatorButtons;
    QPushButton* openDoorButton;
    QPushButton* closeDoorButton;
    QPushButton* helpButton;
    Elevator* owner;        //pointer to the elevator that "owns" this UI
    void blockAllSignals();
    void unblockAllSignals();
};

#endif // ELEVATORUI_H
