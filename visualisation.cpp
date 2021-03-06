#include "visualisation.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QPaintEngine>
#include "bruteforce.h"

Visualisation::Visualisation(QWidget *parent) :
    QWidget(parent),
    mPoints(QVector<QPoint>()),
    mLines(QVector<QLineF>()),
    mAlg(nullptr),
    mTimer(new QElapsedTimer()),
    mElapsed(0)
{

}

void Visualisation::generatePoints(int number)
{
    reset();
    for(int i = 0; i < number; i++)
    {
        int h = QRandomGenerator::global()->bounded(600);
        int w = QRandomGenerator::global()->bounded(600);
        QPoint p(h, w);
        mPoints << p;
    }
    emit update();
}

//determint witch algorithm is used and start call its calc
//number comming from view
void Visualisation::startAlg(int number)
{
    if(mPoints.empty()){ return; }

    switch(number){
        case 0:
            mAlg = new NearestN(mPoints);
            break;
        case 1:
            mAlg = new BruteForce(mPoints);
            break;


        default:
            break;
    }

    mTimer->start();
    mLines = mAlg->calc();
    mElapsed = mTimer->elapsed();
    emit update();
}

//called once a frame or on window.update
void Visualisation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    //undraw
    if(mPoints.empty()){
        painter.eraseRect(0, 0, 600, 600);
        return;
    }

    //draw points
    for(int i = 0; i < mPoints.length(); i++){
        QPoint p = mPoints.at(i);
        QRect r(p.x(), p.y(), 4, 4);

        painter.drawText(p.x(), p.y() - 10, QString::number(i+1));

        painter.fillRect(r, Qt::black);
        painter.drawRect(r);
    }

    //when alg is ready
    if(!mAlg) { return ; }
    if(!mAlg->mDone){ return; }

    //change pencolor and calc length again + draw line
    painter.setPen(QPen(Qt::blue));
    int length = 0;
    for(auto l : mLines){
        length += l.length();
        painter.drawLine(l);
    }

    //set info
    QString info("Length: " + QString::number(length) + "\nTime spent: " + QString::number(mElapsed) + "ms\n");
    emit setInfo(info);
}

void Visualisation::reset()
{
    mPoints = QVector<QPoint>();

    if(mAlg){
        mAlg->mDone = false;
        delete mAlg;
        mAlg = nullptr;
    }

    emit setInfo("");
}
