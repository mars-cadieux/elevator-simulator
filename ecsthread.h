#ifndef ECSTHREAD_H
#define ECSTHREAD_H

#include <QObject>
#include <QThread>

class ECS;

class ECSThread : public QThread
{
    Q_OBJECT
public:
    explicit ECSThread(QObject *parent, ECS* ecs, int floor, const std::string& dir);
    void run() override;

signals:
    void resultReady(const QString &s);
private:
    ECS* ecs;
    int floor;
    std::string dir;

};

#endif // ECSTHREAD_H
