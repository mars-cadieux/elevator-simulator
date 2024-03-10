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
        void powerOut();
        void fire();

    private slots:
        void on_powerOutButton_released();
        void on_fireButton_released();
        void doSomething();
};
#endif // MAINWINDOW_H
