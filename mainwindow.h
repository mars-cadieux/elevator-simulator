#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    signals:
        void openDoorSignal();
        void closeDoorSignal();
        void helpSignal();
        void destFloorSignal(int floorNum);

    private slots:
        void doSomething();
        void openDoorButtonPressed();
        void closeDoorButtonPressed();
        void on_helpButton_released();
        void on_floor1Button_released();
};
#endif // MAINWINDOW_H
