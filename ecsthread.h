#ifndef ECSTHREAD_H
#define ECSTHREAD_H

#include <QObject>
#include <QThread>

class ECS;

//this class is a thread for the ECS to offload request allocation to so it isn't tied up if a request takes a while to allocate
class ECSThread : public QThread
{
    Q_OBJECT
public:
    //I am aware that the way that I have constructed this thread is janky af and likely horrible practice but hey, it works
    //I tried just making the ECS the parent and changing the parent's type to ECS* but it didn't recognize any of the ECS' member functions
    explicit ECSThread(QObject *parent, ECS* ecs, int floor, const std::string& dir);
    void run() override;

signals:
    void resultReady(const QString &s);

private:
    ECS* ecs;
    int floor;          //floor of the request
    std::string dir;    //direction of the request
};

#endif // ECSTHREAD_H
