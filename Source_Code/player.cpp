#include "player.h"

Player::Player(int id, int m)
{
    playerID=id;
    money=m;
    currentX=2;
    currentY=1;
    pauseState=false;
    direction=1;
    moveDirection=1;
    selectNextMove=0;
    if(playerID==1){
        playerColor=Qt::red;
        colorString="red";
    }
    else if(playerID==2){
        playerColor=Qt::blue;
        colorString="blue";
    }
    else{
        playerColor=Qt::green;
        colorString="green";
    }
}

void Player::setSelectNextMove(int m){
    selectNextMove=m;
}

int Player::getSelectNextMove(){
    return selectNextMove;
}

void Player::setPauseState(bool tag){
    pauseState=tag;
}

bool Player::getPauseState(){
    return pauseState;
}

int Player::getID(){
    return playerID;
}

void Player::setKingName(QString name){
    kingName=name;
}

QString Player::getKingName(){
    return kingName;
}

void Player::addGeneral(General *general){
    ownedGeneral.append(general);
}

QList<General*> Player::getOwnedGeneral(){
    return ownedGeneral;
}

void Player::removeGeneral(General *general){
    for(int i=0;i<ownedGeneral.length();i++){
        if(ownedGeneral[i]->getName()==general->getName()){
            ownedGeneral.removeAt(i);
            break;
        }
    }
}

void Player::setCurrentX(int x){
    currentX=x;
}

int Player::getCurrentX(){
    return currentX;
}

void Player::setCurrentY(int y){
    currentY=y;
}

int Player::getCurrentY(){
    return currentY;
}

void Player::setMoveDirection(int direction){
    moveDirection=direction;
}

int Player::getMoveDirection(){
    return moveDirection;
}

void Player::setMoney(int m){
    money=m;
}

int Player::getMoney(){
    return money;
}

int Player::getRemainGeneral(){
    int remain=0;
    for(int i=0;i<ownedGeneral.length();i++){
        if(ownedGeneral[i]->getHoldCity()==NULL){
            remain++;
        }
    }
    return remain;
}

QColor Player::getPlayerColor(){
    return playerColor;
}

QString Player::getColorString(){
    return colorString;
}

void Player::addItem(QString str,int number){
    QMap<QString,int>::Iterator iter=item.find(str);
    if(iter==item.end()){
        item.insert(str,number);
    }
    else{
        item.insert(str,number+iter.value());
    }
}

QMap<QString, int>* Player::getAllItem(){
    return &item;
}

int Player::getItemNumber(QString str){
    QMap<QString,int>::Iterator iter=item.find(str);
    return iter.value();
}

void Player::reverseDirection(){
    if(direction==1){
        direction=2;
    }
    else{
        direction=1;
    }
}

int Player::getDirection(){
    return direction;
}

void Player::playerMove(int direction){
    if(!pauseState){
        if(direction==1){
            switch(moveDirection){
                case 1: currentX--;
                        if(currentX==1){
                            moveDirection=2;
                        }
                        break;
                case 2: currentY++;
                        if(currentY==18){
                            moveDirection=3;
                        }
                        break;
                case 3: currentX++;
                        if(currentX==18){
                            moveDirection=4;
                        }
                        break;
                case 4: currentY--;
                        if(currentY==1){
                            moveDirection=1;
                        }
                        break;
                default: break;
            }
        }
        else{
            switch(moveDirection){
                case 1: currentX++;
                        if(currentX==18){
                            moveDirection=4;
                        }
                        break;
                case 2: currentY--;
                        if(currentY==1){
                            moveDirection=1;
                        }
                        break;
                case 3: currentX--;
                        if(currentX==1){
                            moveDirection=2;
                        }
                        break;
                case 4: currentY++;
                        if(currentY==18){
                            moveDirection=3;
                        }
                        break;
                default: break;
            }
        }
    }
}
