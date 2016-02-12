#include "showinfo.h"
#include "ui_showinfo.h"

ShowInfo::ShowInfo(QWidget *parent, QList<Player> *player) :
    QWidget(parent),
    ui(new Ui::ShowInfo)
{
    ui->setupUi(this);
    setInfo(*player);
    this->setWindowTitle("游戏信息");
}

ShowInfo::~ShowInfo()
{
    delete ui;
}

void ShowInfo::setInfo(QList<Player> player){
    ui->player1Label->setText(player[0].getKingName()+":");
    if(player[0].getOwnedGeneral().length()>0){
        ui->player1List->addItem(new QListWidgetItem("将军:"));
        for(int i=0;i<player[0].getOwnedGeneral().length();i++){
            ui->player1List->addItem(new QListWidgetItem(player[0].getOwnedGeneral()[i]->getName()));
            ui->player1List->addItem(new QListWidgetItem("攻击力:"+QString::number(player[0].getOwnedGeneral()[i]->getTotalAttack())));
            ui->player1List->addItem(new QListWidgetItem("武器:"+player[0].getOwnedGeneral()[i]->getWeapon()));
            ui->player1List->addItem(new QListWidgetItem("-------------------"));
        }
    }

    ui->player1List->addItem(new QListWidgetItem("占领城市:"));
    for(int i=0;i<player[0].getOwnedGeneral().length();i++){
        if(player[0].getOwnedGeneral()[i]->getHoldCity()!=NULL){
           ui->player1List->addItem(new QListWidgetItem(player[0].getOwnedGeneral()[i]->getHoldCity()->getCityName()+"("+player[0].getOwnedGeneral()[i]->getName()+")"));
           ui->player1List->addItem(new QListWidgetItem("等级:"+QString::number(player[0].getOwnedGeneral()[i]->getHoldCity()->getCityLevel())));
           ui->player1List->addItem(new QListWidgetItem("过路费:"+QString::number(player[0].getOwnedGeneral()[i]->getHoldCity()->getCrossFee())));
           ui->player1List->addItem(new QListWidgetItem("-------------------"));
        }
    }
    if(!(*player[0].getAllItem()).isEmpty()){
        ui->player1List->addItem(new QListWidgetItem("持有道具:"));
        QMapIterator<QString,int> iter(*(player[0].getAllItem()));
        while(iter.hasNext()){
            iter.next();
            ui->player1List->addItem(new QListWidgetItem((iter.key()+"  X  "+QString::number(iter.value()))));
            ui->player1List->addItem(new QListWidgetItem("-------------------"));
        }
    }
    ui->player2Label->setText(player[1].getKingName()+":");
    if(player[1].getOwnedGeneral().length()>0){
    ui->player2List->addItem(new QListWidgetItem("将军:"));
    for(int i=0;i<player[1].getOwnedGeneral().length();i++){
        ui->player2List->addItem(new QListWidgetItem(player[1].getOwnedGeneral()[i]->getName()));
        ui->player2List->addItem(new QListWidgetItem("攻击力:"+QString::number(player[1].getOwnedGeneral()[i]->getTotalAttack())));
        ui->player2List->addItem(new QListWidgetItem("武器:"+player[1].getOwnedGeneral()[i]->getWeapon()));
        ui->player2List->addItem(new QListWidgetItem("-------------------"));
    }
    }
    ui->player2List->addItem(new QListWidgetItem("占领城市:"));
    for(int i=0;i<player[1].getOwnedGeneral().length();i++){
        if(player[1].getOwnedGeneral()[i]->getHoldCity()!=NULL){
           ui->player2List->addItem(new QListWidgetItem(player[1].getOwnedGeneral()[i]->getHoldCity()->getCityName()+"("+player[1].getOwnedGeneral()[i]->getName()+")"));
           ui->player2List->addItem(new QListWidgetItem("等级:"+QString::number(player[1].getOwnedGeneral()[i]->getHoldCity()->getCityLevel())));
           ui->player2List->addItem(new QListWidgetItem("过路费:"+QString::number(player[1].getOwnedGeneral()[i]->getHoldCity()->getCrossFee())));
           ui->player2List->addItem(new QListWidgetItem("-------------------"));
        }
    }
    if(!(*player[1].getAllItem()).isEmpty()){
    ui->player2List->addItem(new QListWidgetItem("持有道具:"));
    QMapIterator<QString,int> iter((*player[1].getAllItem()));
    while(iter.hasNext()){
        iter.next();
        ui->player2List->addItem(new QListWidgetItem((iter.key()+"  X  "+QString::number(iter.value()))));
        ui->player2List->addItem(new QListWidgetItem("-------------------"));
    }
    }
    if(player.length()<3){
        ui->player3Label->hide();
        ui->player3List->hide();
    }
    else{
        ui->player3Label->setText(player[2].getKingName()+":");
        if(player[2].getOwnedGeneral().length()>0){
        ui->player3List->addItem(new QListWidgetItem("将军:"));
        for(int i=0;i<player[2].getOwnedGeneral().length();i++){
            ui->player3List->addItem(new QListWidgetItem(player[2].getOwnedGeneral()[i]->getName()));
            ui->player3List->addItem(new QListWidgetItem("攻击力:"+QString::number(player[2].getOwnedGeneral()[i]->getTotalAttack())));
            ui->player3List->addItem(new QListWidgetItem("武器:"+player[2].getOwnedGeneral()[i]->getWeapon()));
            ui->player3List->addItem(new QListWidgetItem("-------------------"));
        }
        }
        ui->player3List->addItem(new QListWidgetItem("占领城市:"));
        for(int i=0;i<player[2].getOwnedGeneral().length();i++){
            if(player[2].getOwnedGeneral()[i]->getHoldCity()!=NULL){
               ui->player3List->addItem(new QListWidgetItem(player[2].getOwnedGeneral()[i]->getHoldCity()->getCityName()+"("+player[2].getOwnedGeneral()[i]->getName()+")"));
               ui->player3List->addItem(new QListWidgetItem("等级:"+QString::number(player[2].getOwnedGeneral()[i]->getHoldCity()->getCityLevel())));
               ui->player3List->addItem(new QListWidgetItem("过路费:"+QString::number(player[2].getOwnedGeneral()[i]->getHoldCity()->getCrossFee())));
               ui->player3List->addItem(new QListWidgetItem("-------------------"));
            }
        }
        if(!(*player[2].getAllItem()).isEmpty()){
        ui->player3List->addItem(new QListWidgetItem("持有道具:"));
        QMapIterator<QString,int> iter((*player[2].getAllItem()));
        while(iter.hasNext()){
            iter.next();
            ui->player3List->addItem(new QListWidgetItem((iter.key()+"  X  "+QString::number(iter.value()))));
            ui->player3List->addItem(new QListWidgetItem("-------------------"));
        }
        }
    }
}
