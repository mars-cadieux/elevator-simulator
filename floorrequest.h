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
    //the actual constructor with proper data is private so only friend classes can instantiate real floor requests
    //I know this is weird/bad practice, initially the FloorRequest class was contained inside the ECS class but I had to take it out so that the ECSThread class could make floor requests
    //TODO: move the generation of floor requests into handleResults() and move this class back into ECS
    FloorRequest(int f, const std::string& dir, int id): floorNum(f), direction(dir), eID(id) {};
    int floorNum;
    std::string direction;
    int eID;    //id of the elevator that is taking the request

};

#endif // FLOORREQUEST_H
