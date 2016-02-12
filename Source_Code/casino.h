#ifndef CASINO_H
#define CASINO_H

#include <QWidget>

namespace Ui {
class Casino;
}

class Casino : public QWidget
{
    Q_OBJECT

public:
    explicit Casino(QWidget *parent = 0, int max=0);
    ~Casino();

    void setRandom();

    void closeEvent(QCloseEvent *e);

signals:
    void sendCasino(int result, QString state);

private slots:
    void on_Btn_clicked();

private:
    Ui::Casino *ui;
    int maxMoney;
};

#endif // CASINO_H
