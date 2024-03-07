#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "elevator.h"

#include <QObject>
#include <vector>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void launch();

signals:

private:
    std::vector<Elevator*> elevators;
    std::vector<MainWindow*> windows;
    Building b;

};

#endif // CONTROLLER_H
