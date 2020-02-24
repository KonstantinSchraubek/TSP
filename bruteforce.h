#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <QMainWindow>
#include "algo.h"

class BruteForce : public Algo
{
public:
    BruteForce(QVector<QPoint> points);
    QVector<QLineF> calc();

private:
    int lineLength(QVector<QLineF>& lines);
    unsigned int factorial(unsigned int n);
    void generateGraph();

private:
    QVector<QVector<QLineF>> mGraph;
};

#endif // BRUTEFORCE_H
