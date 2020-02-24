#include "bruteforce.h"
#include <QThread>
#include <QLineF>
#include <QDebug>
#include <algorithm>

BruteForce::BruteForce(QVector<QPoint> points) : Algo(points)
{

}

QVector<QLineF> BruteForce::calc()
{
    QVector<QLineF> lines;

    generateGraph();

    QVector<int> vertex;
    for (int i = 0; i < mGraph[0].size();i++) {
        if(i != 0){
            vertex.push_back(i);
        }
    }

    int min_path = INT_MAX;
    do {
        int k = 0;
        QVector<QLineF> tryy;

        for(int i = 0; i < vertex.size(); i++){            
            tryy << mGraph[k][vertex[i]];
            k = vertex[i];
        }
        tryy << mGraph[k][0];

        int currentpath = lineLength(tryy);
        if(currentpath < min_path){
            min_path = currentpath;
            lines = tryy;
        }

        min_path = std::min(min_path, lineLength(tryy));
    } while(std::next_permutation(vertex.begin(), vertex.end()));

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

void BruteForce::generateGraph()
{
    for(int i = 0; i < mPoints.size(); i++){
        QVector<QLineF> len;
        for(int j = 0; j < mPoints.size(); j++){
            QLineF l(mPoints[i].x(), mPoints[i].y(), mPoints[j].x(), mPoints[j].y());
            len << l;
        }
        mGraph << len;
    }
}
