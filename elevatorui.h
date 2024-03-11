#ifndef ELEVATORUI_H
#define ELEVATORUI_H

#include "elevatorbutton.h"
#include "defs.h"

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>

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
    void updateDisplayLabel();

private:
    std::vector<ElevatorButton*> elevatorButtons;
    QPushButton* openDoorButton;
    QPushButton* closeDoorButton;
    QPushButton* helpButton;

    QFrame line;
    QLabel userView;
    QLabel display;
    QLabel safetyTests;

    QPushButton* obstructButton;
    QPushButton* overloadButton;

    Elevator* owner;        //pointer to the elevator that "owns" this UI

    void blockAllSignals();
    void unblockAllSignals();
};

#endif // ELEVATORUI_H
