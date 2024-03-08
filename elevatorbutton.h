#ifndef ELEVATORBUTTON_H
#define ELEVATORBUTTON_H

#include <QWidget>
#include <QPushButton>

class ElevatorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ElevatorButton(QPushButton *parent = nullptr);
    ElevatorButton(int floorNum);

    int getFloorNum();

signals:
    void pressed(int floorNum);

private:
    int floorNum;

};

#endif // ELEVATORBUTTON_H
