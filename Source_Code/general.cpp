#include "general.h"

General::General(QString n, int a)
{
    name=n;
    attack=a;
    holdCity=NULL;
    ownedByPlayer=NULL;
    weapon="无";
}

void General::setWeapon(QString w){
    weapon=w;
}

QString General::getWeapon(){
    return weapon;
}

void General::setAttack(int a){
    attack=a;
}

int General::getSelfAttack(){
    return attack;
}

int General::getTotalAttack(){
    return attack+weapon.mid(weapon.indexOf("+")+1,1).toInt();
}

QString General::getName(){
    return name;
}

void General::setHoldCity(City *city){
    holdCity=city;
}

void General::setOwner(Player *p){
    ownedByPlayer=p;
}

Player* General::getOwner(){
    return ownedByPlayer;
}

City* General::getHoldCity(){
    return holdCity;
}
