#include "elevatorui.h"
#include "elevator.h"
#include "display.h"

#include <cmath>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

ElevatorUI::ElevatorUI(QWidget *parent, Elevator* e)
    : QWidget{parent}
{
    owner = e;

    //variable for the row on the grid that the widgets will get added to, things get funky with the elevator buttons and this variable keeps things clean
    int rowOffset = 0;

    //set the title of the window to the ID of its "owner" elevator
    QString eID = QString::number(owner->getID());
    QWidget::setWindowTitle("Elevator " + eID);

    //create new grid layout, and dynamically generate buttons and add them to this layout
    QGridLayout *layout = new QGridLayout(this);

    userView.setText("User View");
    layout->addWidget(&userView, rowOffset, 0, 1, 3, Qt::AlignCenter);
    rowOffset++;

    display.setStyleSheet("background-color: rgb(202, 237, 235); padding: 5px");
    layout->setRowMinimumHeight(rowOffset, 45);
    layout->addWidget(&display, rowOffset, 0, 1, 3);
    rowOffset++;




    //TODO: label with display

    for(int i=1; i<=NUM_FLOORS; ++i){
        ElevatorButton *button = new ElevatorButton(i);
        elevatorButtons.push_back(button);
        button->setStyleSheet("background-color: rgb(232, 197, 232)");
        //add buttons to widget in a grid with 3 columns
        layout->addWidget(button, std::floor((i-1)/3) + rowOffset,  (i-1)%3);

        //connect(button, SIGNAL(released()), this, SLOT (testFun()));
        connect(button, SIGNAL(released()), owner, SLOT (addStop()));
    }
    rowOffset++;


    //add the open door button, close door button, and help button onto the grid in a single row, starting after the final row of elevator buttons
    openDoorButton = new QPushButton("<|>");
    openDoorButton->setStyleSheet("background-color: rgb(217, 178,237)");
    layout->addWidget(openDoorButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0);
    QObject::connect(openDoorButton, SIGNAL(pressed()), owner, SLOT(openDoorFromGUI()));

    closeDoorButton = new QPushButton(">|<");
    closeDoorButton->setStyleSheet("background-color: rgb(217, 178,237)");
    layout->addWidget(closeDoorButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 1);
    QObject::connect(closeDoorButton, SIGNAL(released()), owner, SLOT(closeDoor()));

    helpButton = new QPushButton("Help");
    helpButton->setStyleSheet("background-color: rgb(235, 143, 172)");
    layout->addWidget(helpButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 2);
    QObject::connect(helpButton, SIGNAL(released()), owner, SLOT(callForHelp()));
    rowOffset++;

    //add a separator line and label for the safety test buttons
    line.setObjectName(QString::fromUtf8("line"));
    line.setGeometry(QRect(320, 150, 118, 3));
    line.setFrameShape(QFrame::HLine);
    line.setFrameShadow(QFrame::Sunken);

    layout->setRowMinimumHeight(std::ceil((NUM_FLOORS+3*rowOffset)/3), 20);
    layout->addWidget(&line, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0, 1, 3);
    rowOffset++;

    safetyTests.setText("Safety Tests");
    layout->addWidget(&safetyTests, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0, 1, 3, Qt::AlignCenter);
    rowOffset++;

    obstructButton = new QPushButton("Door Obstruction");
    obstructButton->setCheckable(true);
    layout->addWidget(obstructButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0, 1, 3);
    QObject::connect(obstructButton, SIGNAL(released()), owner, SLOT(obstructedToggle()));
    rowOffset++;

    overloadButton = new QPushButton("Overload");
    overloadButton->setCheckable(true);
    layout->addWidget(overloadButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0, 1, 3);
    QObject::connect(overloadButton, SIGNAL(released()), owner, SLOT(overloadToggle()));
    rowOffset++;

    fireButton = new QPushButton("Fire");
    layout->addWidget(fireButton, std::ceil((NUM_FLOORS+3*rowOffset)/3), 0, 1, 3);
    QObject::connect(fireButton, SIGNAL(released()), owner, SLOT(fire()));
    rowOffset++;
}


ElevatorUI::~ElevatorUI()
{
    for(unsigned int i=0; i<elevatorButtons.size(); ++i){
        delete elevatorButtons[i];
    }
    elevatorButtons.clear();
    delete openDoorButton;
    delete closeDoorButton;
    delete helpButton;
    delete obstructButton;
    delete overloadButton;
}

void ElevatorUI::updateDisplayLabel()
{
    Display* d = qobject_cast<Display*>(sender());
    string msg = d->getMessage();
    display.setText(QString::fromStdString(msg));
}

void ElevatorUI::blockAllSignals()
{
    for(unsigned int i=0; i<elevatorButtons.size(); ++i){
        elevatorButtons[i]->blockSignals(true);
    }
    openDoorButton->blockSignals(true);
    closeDoorButton->blockSignals(true);
    helpButton->blockSignals(true);
    obstructButton->blockSignals(true);
    obstructButton->setCheckable(false);
    overloadButton->blockSignals(true);
    overloadButton->setCheckable(false);
}

void ElevatorUI::unblockAllSignals()
{
    for(unsigned int i=0; i<elevatorButtons.size(); ++i){
        elevatorButtons[i]->blockSignals(false);
    }
    openDoorButton->blockSignals(false);
    closeDoorButton->blockSignals(false);
    helpButton->blockSignals(false);
    obstructButton->blockSignals(false);
    obstructButton->setCheckable(true);
    overloadButton->blockSignals(false);
    overloadButton->setCheckable(true);
}
