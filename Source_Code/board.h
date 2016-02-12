#ifndef BOARD_H
#define BOARD_H
#include <QList>
#include <QTimer>
#include "player.h"
#include "city.h"

#include <QWidget>

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = 0, QStringList *gameInfo=NULL);
    ~Board();

    void initBoard();

    void initGame(QStringList *info);

    void initCity();

    void afterMove();

    void cityMove();

    void occupiedCity(int index);

    void upgradeCity(int index);

    void fightOrPay(int index);

    void fight(int index);

    int getFightResult(General *g1, General *g2);

    void setRandom();

    void finalStep();

    void corrupt();

    void switchCityGeneral(int index);


private slots:
    void gameRun();

    void move();

    void getGeneralData(QString general,QString state);

    void getCasinoData(int money, QString state);

    void getbuyList(QList<QString> buyList, QList<int> buyNum, int remainMoney);

    void showMapInfo(int x, int y);

    void on_quitGameBtn_clicked();

    void on_checkInfoBtn_clicked();

    void on_useItemBtn_clicked();


private:
    Ui::Board *ui;
    int playerNum;
    int startNum;
    int initMoney;
    int baseOccupiedMoney;
    int baseupgradeMoney;
    int whoseTurn;
    int startX;
    int startY;
    QList<General> general;
    QList<Player> player;
    QList<City> city;
    QTimer *timer;
    int currentDice;
    int gameSpeed;
    int currentCity;
    int generalPrice;

};

#endif // BOARD_H
