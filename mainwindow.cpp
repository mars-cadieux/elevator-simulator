#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "elevatorbutton.h"
#include "floorbutton.h"
#include "defs.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //create a grid layout that we will add all our buttons and widgets to
    QGridLayout *layout = new QGridLayout();
    widgets.push_back(layout);

    //set up the UI , needs to be done before we can start adding things to our layout
    ui->setupUi(this);

    layout->setColumnMinimumWidth(1, 10);

    //generate the floors and their floor buttons, these will be added to the GUI in reverse order so floor 7 is at the top (row 0) and floor 1 is at the bottom (row 6)
    //this GUI is dynamic, so the number of floors can be changed and it will still generate everything needed for each floor
    for(int i=1; i<=NUM_FLOORS; ++i){

        //generate a label for each floor with the floor number
        QLabel* floorLabel = new QLabel(this);
        floorLabel->setText(QString::number(i));
        layout->addWidget(floorLabel, 3*(NUM_FLOORS -i)+1, 0, 2, 1, Qt::AlignRight);

        //generate the "up" button for each floor except the final floor
        if(i != NUM_FLOORS){
            FloorButton* upButton = new FloorButton(this, i, "up");
            floorButtons.push_back(upButton);
            layout->addWidget(upButton, 3*(NUM_FLOORS -i)+1, 1);
            connect(upButton, SIGNAL(released()), this, SLOT (floorButtonReleased()));
        }

        //generate the "down" button for each floor except the first floor
        if(i != 1){
            FloorButton* downButton = new FloorButton(this, i, "down");
            floorButtons.push_back(downButton);
            layout->addWidget(downButton, 3*(NUM_FLOORS -i) +2, 1);
            connect(downButton, SIGNAL(released()), this, SLOT (floorButtonReleased()));
        }


        //QSpacerItem* spacer = new QSpacerItem(10, 10);

        //add a horizontal line between each set of floor buttons
        if(i != NUM_FLOORS){
            QFrame* line = new QFrame(this);
            line->setObjectName(QString::fromUtf8("line"));
            line->setGeometry(QRect(320, 150, 118, 3));
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);

            layout->setRowMinimumHeight(3*i, 20);
            layout->addWidget(line, 3*(NUM_FLOORS -i), 1);
        }

    }

    //add the power outage button and connect it to its slot
    QPushButton* powerOutButton = new QPushButton("Power Out", this);
    layout->setColumnMinimumWidth(2, 50);
    layout->addWidget(powerOutButton, NUM_FLOORS*3/2, 2, Qt::AlignRight);

    connect(powerOutButton, SIGNAL(released()), this, SLOT (on_powerOutButton_released()));

    //add the fire button and connect it to its slot
    QPushButton* fireButton = new QPushButton("Fire", this);
    layout->addWidget(fireButton, NUM_FLOORS*3/2 + 1, 2, Qt::AlignRight);

    connect(fireButton, SIGNAL(released()), this, SLOT (on_fireButton_released()));

    //now add the grid layout to a new widget and set the central widget of MainWindow to this new widget
    QWidget *window = new QWidget(this);
    window->setLayout(layout);

    setCentralWidget(window);


}

MainWindow::~MainWindow()
{

    for(unsigned int i=0; i<widgets.size(); ++i){
        delete widgets[i];
    }
    widgets.clear();

    delete ui;
}

//unblocks all signals
void MainWindow::resume()
{
    this->blockSignals(false);
}



void MainWindow::on_powerOutButton_released()
{
    emit powerOut();
    for(unsigned int i=0; i<floorButtons.size(); ++i){
        floorButtons[i]->darken();
    }
    //block all signals until the ECS tells us the simulation is good to be resumed
    this->blockSignals(true);
}

void MainWindow::on_fireButton_released()
{
    emit fire();
    for(unsigned int i=0; i<floorButtons.size(); ++i){
        floorButtons[i]->darken();
    }
    //block all signals until the ECS tells us the simulation is good to be resumed
    this->blockSignals(true);
}

void MainWindow::floorButtonReleased(){
    //qInfo("test");
    FloorButton* fButton = qobject_cast<FloorButton*>(sender());
    int floor = fButton->getFloorNum();
    string dir = fButton->getDirection();
    //fButton->illuminate();
    emit floorButtonPressed(floor, dir);
    //cout<<"floor "<<floor<<" "<<dir<<" requested"<<endl;
}

//adds a delay
void MainWindow::delay(int seconds)
{
    QTime dieTime= QTime::currentTime().addSecs(seconds);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void MainWindow::pendingRequest(int f, const string &dir)
{
    for(unsigned int i=0; i<floorButtons.size(); ++i){
        if(floorButtons[i]->getFloorNum() == f && floorButtons[i]->getDirection() == dir){
            floorButtons[i]->illuminate();
        }
    }
}

//if a floor button's request has failed, it should wait 1 second then make its request again
//we wait 1 second so we don't overload the ECS
void MainWindow::failedRequest(int f, const std::string &dir)
{
    qInfo("request failed");
    delay(1);
    emit floorButtonPressed(f, dir);
}

void MainWindow::completedRequest(int f, const std::string &dir)
{
    for(unsigned int i=0; i<floorButtons.size(); ++i){
        if(floorButtons[i]->getFloorNum() == f && floorButtons[i]->getDirection() == dir){
            floorButtons[i]->darken();
        }
    }
}

