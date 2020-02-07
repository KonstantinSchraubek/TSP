#ifndef ALGO_H
#define ALGO_H

#include <QVector>
#include <QPoint>
#include <QLineF>

class Algo{
public:
    Algo(QVector<QPoint> p) : mDone(false), mPoints(p){}
    virtual ~Algo(){}
    virtual QVector<QLineF> calc() = 0;
    bool mDone;
protected:
    QVector<QPoint> mPoints;
};

#endif // ALGO_H
