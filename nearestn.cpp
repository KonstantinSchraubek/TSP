#include "nearestn.h"
#include <QLineF>

NearestN::NearestN(QVector<QPoint> points) : Algo(points)
{
}

QVector<QLineF> NearestN::calc()
{
    QVector<QLineF> lines;

    QVector<QPoint> copy(mPoints);

    int lastPoint = 0;

    while(lines.size() != mPoints.size() - 1){
        int minLenght = INT_MAX;
        int point = INT_MAX;
        QLineF line;
        for(auto p : copy){
            if(mPoints.indexOf(p) == lastPoint){
                continue;
            }

            QLineF l(mPoints[lastPoint].x(), mPoints[lastPoint].y(), p.x(), p.y());
            if(l.length() < minLenght){
                minLenght = l.length();
                point = mPoints.indexOf(p);
                line = l;
            }
        }

        copy.removeOne(mPoints[point]);
        lines << line;

        //remove startpoint
        if(lastPoint == 0){
            copy.removeOne(mPoints[lastPoint]);
        }

        lastPoint = point;
    }

    //line from last to first
    QLineF l(mPoints[0].x(), mPoints[0].y(), lines.last().p2().x(), lines.last().p2().y());
    lines << l;

    mDone = true;
    return lines;
}
