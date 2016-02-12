#include "city.h"

City::City(QString name, int x, int y)
{
    cityName=name;
    cityLevel=1;
    crossFee=100;
    markX=x;
    markY=y;
    holdByGeneral=NULL;
}

QString City::getCityName(){
    return cityName;
}

void City::setCityLevel(int level){
    cityLevel=level;
}

int City::getCityLevel(){
    return cityLevel;
}

void City::setCrossFee(int fee){
    crossFee=fee;
}

int City::getCrossFee(){
    return crossFee;
}

void City::setHoldGeneral(General* hold){
    holdByGeneral=hold;
}

General* City::getHoldGeneral(){
    return holdByGeneral;
}

int City::getMarkX(){
    return markX;
}

int City::getMarkY(){
    return markY;
}
