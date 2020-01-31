#ifndef VISUALISATION_H
#define VISUALISATION_H

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QElapsedTimer>
#include "algo.h"
#include "nearestn.h"

class Visualisation : public QWidget
{
    Q_OBJECT
public:
    explicit Visualisation(QWidget *parent = nullptr);

signals:
    void setInfo(const QString &info);

public slots:
    void generatePoints(int number);
    void startAlg(int number);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);

private:
    void reset();

private:
    QVector<QPoint> mPoints;
    QVector<QLineF> mLines;
    Algo* mAlg;
    QElapsedTimer* mTimer;
    quint64 mElapsed;
};

#endif // VISUALISATION_H
