#include "bruteforce.h"
#include <QThread>
#include <QLineF>
#include <QDebug>

BruteForce::BruteForce(QVector<QPoint> points) : Algo(points)
{

}

QVector<QLineF> BruteForce::calc()
{
    QVector<QLineF> lines;
    QVector<QVector<QPoint>> allPosibilities;
    QPoint start = mPoints[0];

    for(int j = 0; j < mPoints.size(); j++){
        QVector<QPoint> points;
        points << start;

        for(int i = 1; i < mPoints.size(); i++){
            points << mPoints[i];
        }

        points << start;
        allPosibilities << points;
    }

    if(allPosibilities.size() != factorial(mPoints.length())){
        qDebug() <<"not all hit - bruteforce";
    }

    QVector<QLineF> min;
    int minInt = INT_MAX;
    for(auto vec : allPosibilities){
        QVector<QLineF> tryy;
        for(int j = 0; j < vec.length(); j++){
            if(j == vec.size() - 1){
                continue;
            }
            QLineF l(vec[j].x(), vec[j].y(), vec[j+1].x(), vec[j+1].y());
            tryy << l;
        }
        int len = lineLength(tryy);
        if(len < minInt){
            minInt = len;
            min = tryy;
        }
    }

    lines = min;

    mDone = true;
    return lines;
}

int BruteForce::lineLength(QVector<QLineF> &lines)
{
    int res = 0;
    for(auto l : lines){
        res += l.length();
    }
    return res;
}

unsigned int BruteForce::factorial(unsigned int n)
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}
