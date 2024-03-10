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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{





    QGridLayout *layout = new QGridLayout;


    ui->setupUi(this);

    for(int i=1; i<=NUM_FLOORS; ++i){

        FloorButton* upButton = new FloorButton(this, i, "up");
        layout->addWidget(upButton, 3*i -2, 0);
        //upButton->show();
        connect(upButton, SIGNAL(released()), this, SLOT (doSomething()));

        FloorButton* downButton = new FloorButton(this, i, "down");
        layout->addWidget(downButton, 3*i -1, 0);
        //downButton->show();
        connect(downButton, SIGNAL(released()), this, SLOT (doSomething()));

        //QSpacerItem* spacer = new QSpacerItem(10, 10);

        if(i != NUM_FLOORS){
            QFrame* line = new QFrame(this);
            line->setObjectName(QString::fromUtf8("line"));
            line->setGeometry(QRect(320, 150, 118, 3));
            line->setFrameShape(QFrame::HLine);
            line->setFrameShadow(QFrame::Sunken);

            layout->setRowMinimumHeight(3*i, 20);
            layout->addWidget(line, 3*i, 0);
        }

    }

    QPushButton* test = new QPushButton("test");

    layout->addWidget(test, NUM_FLOORS*3/2, 2);

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
    qInfo("test");
}

