#ifndef NEARESTN_H
#define NEARESTN_H
#include <QDebug>
#include <QPoint>
#include <QVector>
#include "algo.h"

class NearestN : public Algo
{
public:
    NearestN(QVector<QPoint> points);
    QVector<QLineF> calc();
};

#endif // NEARESTN_H
