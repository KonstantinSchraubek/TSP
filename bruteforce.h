#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <QMainWindow>
#include "algo.h"

class BruteForce : public Algo
{
public:
    BruteForce(QVector<QPoint> points);
    QVector<QLineF> calc();
    int lineLength(QVector<QLineF>& lines);
    unsigned int factorial(unsigned int n);
};

#endif // BRUTEFORCE_H
