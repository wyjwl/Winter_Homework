#ifndef PLAYER_H
#define PLAYER_H
#include <QColor>
#include <QList>
#include <QMap>
#include "general.h"
#include "city.h"

class General;
class City;
class Player
{
public:
    Player(int id, int m);

    int getID();

    void setKingName(QString name);

    QString getKingName();

    void addGeneral(General *general);

    QList<General*> getOwnedGeneral();

    void removeGeneral(General *general);

    void setCurrentX(int x);

    int getCurrentX();

    void setCurrentY(int y);

    int getCurrentY();

    void setMoveDirection(int direction);

    int getMoveDirection();

    void playerMove(int direction);

    QColor getPlayerColor();

    QString getColorString();

    void setMoney(int m);

    int getMoney();

    int getRemainGeneral();

    void addItem(QString str, int number);

    QMap<QString, int>* getAllItem();

    int getItemNumber(QString str);

    void reverseDirection();

    int getDirection();

    void setPauseState(bool tag);

    bool getPauseState();

    void setSelectNextMove(int m);

    int getSelectNextMove();

private:
    int playerID;
    QString kingName;
    int money;
    bool haveItem;
    QList<General*> ownedGeneral;
    QList<City*> ownedCity;
    int currentX;
    int currentY;
    int moveDirection;
    QColor playerColor;
    QString colorString;
    QMap<QString, int> item;
    int direction;
    bool pauseState;
    int selectNextMove;
};

#endif // PLAYER_H
