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

void Visualisation::startAlg(int number)
{
    if(mPoints.empty()){ return; }

    switch(number){
        case 0:
            mAlg = new NearestN(mPoints);
            break;
        case 1:
            mAlg = new BruteForce(mPoints);
        default:
            break;
    }

    mTimer->start();
    mLines = mAlg->calc();
    mElapsed = mTimer->elapsed();
    emit update();
}

void Visualisation::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);

    if(mPoints.empty()){
        painter.eraseRect(0, 0, 600, 600);
        return;
    }

    for(int i = 0; i < mPoints.length(); i++){
        QPoint p = mPoints.at(i);
        QRect r(p.x(), p.y(), 4, 4);

        painter.drawText(p.x(), p.y() - 10, QString::number(i+1));

        painter.fillRect(r, Qt::black);
        painter.drawRect(r);
    }

    if(!mAlg) { return ; }
    if(!mAlg->mDone){ return; }

    int length = 0;
    for(auto l : mLines){
        length += l.length();
        painter.drawLine(l);
    }

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
