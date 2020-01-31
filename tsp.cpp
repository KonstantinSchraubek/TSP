#include "tsp.h"
#include "ui_tsp.h"
#include <QPainter>
#include <QDebug>

TSP::TSP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TSP)
{
    ui->setupUi(this);

    connect(ui->startButton, &QPushButton::clicked, this, &TSP::startClicked);
    connect(ui->generateButton, &QPushButton::clicked, this, &TSP::generateClicked);
    connect(this, &TSP::generate, ui->vis, &Visualisation::generatePoints);
    connect(this, &TSP::start, ui->vis, &Visualisation::startAlg);

    connect(ui->vis, &Visualisation::setInfo, this, &TSP::setInfo);
}

TSP::~TSP()
{
    delete ui;
}

void TSP::generateClicked()
{
    emit generate(ui->numberOfPoints->value());
}

void TSP::startClicked()
{
    emit start(ui->comboBox->currentIndex());
}

void TSP::setInfo(const QString &info)
{
    ui->info->setText(info);
}
