#ifndef TSP_H
#define TSP_H

#include <QWidget>

namespace Ui {
class TSP;
}

class TSP : public QWidget
{
    Q_OBJECT

public:
    explicit TSP(QWidget *parent = 0);
    ~TSP();

public slots:
    void generateClicked();
    void startClicked();
    void setInfo(const QString &info);

signals:
    void generate(int number);
    void start(int alg);

private:
    Ui::TSP *ui;
};

#endif // TSP_H
