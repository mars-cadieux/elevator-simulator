#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "floorbutton.h"

#include <QMainWindow>
#include <iostream>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        std::vector<FloorButton*> floorButtons;    //all buttons used on gui, pointers stored in a vector so we can delete them in the destructor
        std::vector<QObject*> widgets;    //all other widgets used on gui (QFrame, window, layouts, etc), pointers stored in a vector so we can delete them in the destructor
        void delay(int seconds);       //function to add a 1 second delay when a floor button is informed that its request has failed

    signals:
        void powerOut();
        void fire();
        void floorButtonPressed(int fn, const std::string& dir);

    public slots:
        void resume();   //unblocks all signals
        void pendingRequest(int f, const std::string& dir);
        void completedRequest(int f, const std::string& dir);

    private slots:
        void powerOutButton_released();
        void fireButton_released();
        void floorButtonReleased();

};
#endif // MAINWINDOW_H
