#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QLabel>

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
        std::vector<QLabel*> labels;    //all labels used on gui, pointers stored in a vector so we can delete them in the destructor
        std::vector<QPushButton*> buttons;    //all buttons used on gui, pointers stored in a vector so we can delete them in the destructor
         std::vector<QObject*> widgets;    //all other widgets used on gui (QFrame, window, layouts, etc), pointers stored in a vector so we can delete them in the destructor

    signals:
        void powerOut();
        void fire();
        void floorButtonPressed(int fn, const std::string& dir);

    public slots:
        void resume();   //unblocks all signals

    private slots:
        void on_powerOutButton_released();
        void on_fireButton_released();
        void floorButtonReleased();
};
#endif // MAINWINDOW_H
