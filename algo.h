#ifndef ALGO_H
#define ALGO_H

#include <QVector>
#include <QPoint>
#include <QLineF>

class Algo{
public:
    Algo(QVector<QPoint> p) : mPoints(p), mDone(false){}
    virtual QVector<QLineF> calc() = 0;
    bool mDone;
protected:
    QVector<QPoint> mPoints;
};

#endif // ALGO_H
