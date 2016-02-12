#ifndef GENERAL_H
#define GENERAL_H
#include <QString>
#include "city.h"
#include "player.h"

class Player;
class City;
class General
{
public:
    General(QString n, int a=10);

    void setAttack(int a);

    int getSelfAttack();

    int getTotalAttack();

    QString getName();

    void setHoldCity(City *city);

    City* getHoldCity();

    void setOwner(Player *p);

    Player* getOwner();

    void setWeapon(QString w);

    QString getWeapon();

private:
    QString name;
    int attack;
    City* holdCity;
    Player* ownedByPlayer;
    QString weapon;
};

#endif // GENERAL_H
