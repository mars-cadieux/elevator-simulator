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





    QGridLayout *layout = new QGridLayout;


    ui->setupUi(this);

    layout->setColumnMinimumWidth(1, 10);

    for(int i=1; i<=NUM_FLOORS; ++i){

        QLabel* floorLabel = new QLabel(this);
        floorLabel->setText(QString::number(i));
        layout->addWidget(floorLabel, 3*(NUM_FLOORS -i)+1, 0, 2, 1, Qt::AlignRight);

        if(i != NUM_FLOORS){
            FloorButton* upButton = new FloorButton(this, i, "up");
            upButton->setFixedWidth(30);
            layout->addWidget(upButton, 3*(NUM_FLOORS -i)+1, 1);
            //upButton->show();
            connect(upButton, SIGNAL(released()), this, SLOT (doSomething()));
        }

        if(i != 1){
            FloorButton* downButton = new FloorButton(this, i, "down");
            layout->addWidget(downButton, 3*(NUM_FLOORS -i) +2, 1);
            downButton->setFixedWidth(30);
            //downButton->show();
            connect(downButton, SIGNAL(released()), this, SLOT (doSomething()));
        }


        //QSpacerItem* spacer = new QSpacerItem(10, 10);

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

    QPushButton* test = new QPushButton("test");

    layout->setColumnMinimumWidth(2, 50);
    layout->addWidget(test, NUM_FLOORS*3/2, 2, Qt::AlignRight);

    QWidget *window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_powerOutButton_released()
{
    emit powerOut();
}

void MainWindow::on_fireButton_released()
{
    emit fire();
}

void MainWindow::doSomething(){
    //qInfo("test");
    FloorButton* fButton = qobject_cast<FloorButton*>(sender());
    int floor = fButton->getFloorNum();
    string dir = fButton->getDirection();
    cout<<"floor "<<floor<<" "<<dir<<" requested"<<endl;
}

