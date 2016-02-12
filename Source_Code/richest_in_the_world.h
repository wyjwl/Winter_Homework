#ifndef RICHEST_IN_THE_WORLD_H
#define RICHEST_IN_THE_WORLD_H

#include <QWidget>

namespace Ui {
class Richest_in_the_world;
}

class Richest_in_the_world : public QWidget
{
    Q_OBJECT

public:
    explicit Richest_in_the_world(QWidget *parent = 0);
    ~Richest_in_the_world();

private slots:
    void on_introductionBtn_clicked();

    void on_newGameBtn_clicked();

private:
    Ui::Richest_in_the_world *ui;
};

#endif // RICHEST_IN_THE_WORLD_H
