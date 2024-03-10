#ifndef FLOORBUTTON_H
#define FLOORBUTTON_H

#include <string>

#include <QWidget>
#include <QPushButton>

using namespace std;

class FloorButton : public QPushButton
{
    Q_OBJECT
public:
    explicit FloorButton(QWidget *parent = nullptr,int floorNum = 0, const string& direction = "");

    int getFloorNum() const;
    const string& getDirection() const;

signals:

private:
    int floorNum;
    string direction;
};

#endif // FLOORBUTTON_H
