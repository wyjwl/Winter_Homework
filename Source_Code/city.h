#ifndef CITY_H
#define CITY_H
#include "player.h"
#include "general.h"

class General;
class City
{
public:
    City(QString name,int x,int y);

    QString getCityName();

    void setCityLevel(int level);

    int getCityLevel();

    void setCrossFee(int fee);

    int getCrossFee();

    void setHoldGeneral(General *hold);

    General* getHoldGeneral();

    int getMarkX();

    int getMarkY();

private:
    QString cityName;
    General *holdByGeneral;
    int cityLevel;
    int crossFee;
    int markX;
    int markY;
};

#endif // CITY_H
