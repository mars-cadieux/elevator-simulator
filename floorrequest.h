#ifndef FLOORREQUEST_H
#define FLOORREQUEST_H

#include <QObject>

class FloorRequest : public QObject
{
    Q_OBJECT
public:
    explicit FloorRequest(QObject *parent = nullptr);
    friend class ECS;
    friend class ECSThread;

signals:

private:
    FloorRequest(int f, const std::string& dir, int id): floorNum(f), direction(dir), eID(id) {};
    int floorNum;
    std::string direction;
    int eID;    //id of the elevator that is taking the request

};

#endif // FLOORREQUEST_H
