#include "nearestn.h"
#include <QLineF>

NearestN::NearestN(QVector<QPoint> points) : Algo(points)
{
}

QVector<QLineF> NearestN::calc()
{
    //result
    QVector<QLineF> lines;
    //deep copy points
    QVector<QPoint> copy(mPoints);

    int lastPoint = 0;

    //loop till lines have same size as points - 1
    while(lines.size() != mPoints.size() - 1){
        int minLenght = INT_MAX;
        int point = INT_MAX;
        QLineF line;
        //try each point
        for(auto p : copy){
            if(mPoints.indexOf(p) == lastPoint){
                continue;
            }

            //Generate a line from current to possible next points; check lenght; if shorter new nearest
            QLineF l(mPoints[lastPoint].x(), mPoints[lastPoint].y(), p.x(), p.y());
            if(l.length() < minLenght){
                minLenght = l.length();
                point = mPoints.indexOf(p);
                line = l;
            }
        }

        //remove selected points from possiblities
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
