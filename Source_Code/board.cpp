#include "board.h"
#include "ui_board.h"
#include "selectgeneral.h"
#include "casino.h"
#include "shop.h"
#include "showinfo.h"
#include "useitem.h"
#include <QTime>
#include <QTimer>
#include <QMessageBox>

Board::Board(QWidget *parent, QStringList *gameInfo) :
    QWidget(parent),
    ui(new Ui::Board)
{
    ui->setupUi(this);
    initBoard();
    initGame(gameInfo);
    this->setWindowTitle("富甲天下混搭大富翁_寒假作业");
    connect( timer, SIGNAL(timeout()),this,SLOT(move()));
    connect(ui->throwDice,SIGNAL(clicked(bool)),this,SLOT(gameRun()));
    connect(ui->checkBoard,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(showMapInfo(int,int)));
}

Board::~Board()
{
    delete ui;
}

void Board::initBoard(){
    for(int i=0;i<ui->checkBoard->columnCount();i++){
        ui->checkBoard->setColumnWidth(i,45);
    }
    ui->checkBoard->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->checkBoard->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->checkBoard->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->checkBoard->setSpan(2,2,16,16);
    startX=2;
    startY=1;
    ui->checkBoard->item(startX,startY)->setBackgroundColor(Qt::red);
    timer=new QTimer();
}

void Board::initGame(QStringList *info){
    baseOccupiedMoney=1000;
    baseupgradeMoney=500;
    gameSpeed=100;
    generalPrice=500;
    startNum=0;
    int id=0;
    QStringList::Iterator itInfo=info->begin();
    playerNum=QString(*itInfo++).toInt();
    initMoney=QString(*itInfo++).toInt();
    while(itInfo!=info->end()){
        if(QString(*itInfo).contains("玩家")){
            player.append(Player(id+1,initMoney));
            itInfo++;
            player[id].setKingName(*itInfo++);
            while(!QString(*itInfo).contains("玩家") && !QString(*itInfo).contains("闲置将军")){
                general.append(General(*itInfo++));
                player[id].addGeneral(&general.last());
                general.last().setOwner(&player[id]);
            }
            id++;
        }
        if(*itInfo=="闲置将军"){
            while(itInfo!=info->end()){
                general.append(*itInfo++);
            }
        }
    }
    whoseTurn=0;
    initCity();
    ui->currentPlayerMoney->setText(QString::number(player[whoseTurn].getMoney()));
}

void Board::initCity(){
    city.append(City("西凉城",0,2));
    city.append(City("长安城",0,7));
    city.append(City("井州城",0,9));
    city.append(City("洛阳城",0,11));
    city.append(City("冀州城",0,15));
    city.append(City("许昌城",2,19));
    city.append(City("徐州城",4,19));
    city.append(City("建业城",12,19));
    city.append(City("柴桑城",16,19));
    city.append(City("长沙城",19,16));
    city.append(City("荆州城",19,13));
    city.append(City("襄阳城",19,7));
    city.append(City("武陵城",19,2));
    city.append(City("成都城",16,0));
    city.append(City("汉中城",6,0));
}

void Board::setRandom(){
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
}

void Board::gameRun(){
    setRandom();
    if(player[whoseTurn].getSelectNextMove()==0){
        currentDice = qrand()%6+1;
    }
    else{
        currentDice=player[whoseTurn].getSelectNextMove();
        player[whoseTurn].setSelectNextMove(0);
    }
    if(!player[whoseTurn].getPauseState()){
        ui->diceNumber->setText(QString::number(currentDice));
    }
    else{
        ui->diceNumber->setText("0");
    }
    ui->throwDice->setEnabled(false);
    move();
}

void Board::move(){
    ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->setBackgroundColor(Qt::white);
    for(int i=0;i<player.length();i++){
        if(i==whoseTurn){
            continue;
        }
        if(player[i].getCurrentX()==player[whoseTurn].getCurrentX() && player[i].getCurrentY()==player[whoseTurn].getCurrentY()){
            ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->setBackgroundColor(player[i].getPlayerColor());
        }
    }
    player[whoseTurn].playerMove(player[whoseTurn].getDirection());
    ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->setBackgroundColor(player[whoseTurn].getPlayerColor());
    currentDice--;
    if(currentDice!=0){
        timer->start(gameSpeed);
    }
    else{
        timer->stop();
        player[whoseTurn].setPauseState(false);
        afterMove();
    }
}

void Board::corrupt(){
    QMessageBox::about(NULL,player[whoseTurn].getKingName(), "破产咯");
    for(int i=0;i<city.length();i++){
        if(city[i].getHoldGeneral()!=NULL){
            if(city[i].getHoldGeneral()->getOwner()->getKingName()==player[whoseTurn].getKingName()){
               city[i].getHoldGeneral()->setHoldCity(NULL);
               city[i].setHoldGeneral(NULL);
               ui->checkBoard->setItem(city[i].getMarkX(),city[i].getMarkY(),new QTableWidgetItem(" "));
            }
        }
    }
    for(int i=0;i<general.length();i++){
        if(general[i].getOwner()!=NULL){
            if(general[i].getOwner()->getKingName()==player[whoseTurn].getKingName()){
               general[i].setOwner(NULL);
            }
        }
    }
    player.removeAt(whoseTurn);
    playerNum--;
}

void Board::finalStep(){
    if(player[whoseTurn].getMoney()<0){
        corrupt();
    }
    ui->throwDice->setEnabled(true);
    whoseTurn++;
    if(whoseTurn>=playerNum){
        whoseTurn=0;
    }
    ui->playerTurn->setText("当前轮到:"+player[whoseTurn].getKingName());
    ui->playerTurn->setStyleSheet("color:"+player[whoseTurn].getColorString());
    ui->currentPlayerMoney->setText(QString::number(player[whoseTurn].getMoney()));
    if(playerNum<2){
        QMessageBox::about(NULL,"游戏结束", player[0].getKingName()+"胜利");
        on_quitGameBtn_clicked();
    }
}

int Board::getFightResult(General *g1, General *g2){
    float generalWinRate=10*(float(g1->getTotalAttack())/(float(g1->getTotalAttack()+g2->getTotalAttack())));
    setRandom();
    float ran=qrand()%10+1;
    if(ran<generalWinRate){
        return 1;
    }
    else{
        return 2;
    }
}

void Board::getbuyList(QList<QString> buyList, QList<int> buyNum, int remainMoney){
    for(int i=0;i<buyList.length();i++){
        player[whoseTurn].addItem(buyList[i],buyNum[i]);
    }
    player[whoseTurn].setMoney(remainMoney);
    finalStep();
}

void Board::getGeneralData(QString generalName, QString state){
    if(state=="守城"){
        for(int i=0;i<general.length();i++){
            if(general[i].getName()==generalName){
                player[whoseTurn].setMoney(player[whoseTurn].getMoney()-baseOccupiedMoney);
                general[i].setHoldCity(&city[currentCity]);
                city[currentCity].setHoldGeneral(&general[i]);
                ui->checkBoard->setItem(city[currentCity].getMarkX(),city[currentCity].getMarkY(),new QTableWidgetItem(player[whoseTurn].getKingName()+"("+QString::number(city[currentCity].getCityLevel())+"级)"));
    //            ui->checkBoard->item(city[currentCity].getMarkX(),city[currentCity].getMarkY())->setBackgroundColor(player[whoseTurn].getPlayerColor());
                break;
            }
        }
    }
    else if(state=="出战"){
        for(int i=0;i<general.length();i++){
            if(general[i].getName()==generalName){
                int result=getFightResult(&general[i],city[currentCity].getHoldGeneral());
                if(result==1){
                    QMessageBox::about(NULL,city[currentCity].getCityName(),general[i].getName()+"胜利 "+ city[currentCity].getCityName()+"被"+player[whoseTurn].getKingName()+"占领!");
                    city[currentCity].getHoldGeneral()->setHoldCity(NULL);
                    city[currentCity].getHoldGeneral()->getOwner()->removeGeneral(city[currentCity].getHoldGeneral());
                    city[currentCity].getHoldGeneral()->setOwner(NULL);
                    city[currentCity].setHoldGeneral(&general[i]);
                    general[i].setHoldCity(&city[currentCity]);
                    ui->checkBoard->setItem(city[currentCity].getMarkX(),city[currentCity].getMarkY(),new QTableWidgetItem(city[currentCity].getHoldGeneral()->getOwner()->getKingName()+"("+QString::number(city[currentCity].getCityLevel())+"级)"));
                }
                else{
                    QMessageBox::about(NULL,city[currentCity].getCityName(),city[currentCity].getHoldGeneral()->getName()+"胜利 "+ player[whoseTurn].getKingName()+"支付双倍("+QString::number(city[currentCity].getCrossFee()*2)+")过路费!");
                    player[whoseTurn].setMoney(player[whoseTurn].getMoney()-city[currentCity].getCrossFee()*2);
                    city[currentCity].getHoldGeneral()->getOwner()->setMoney(city[currentCity].getHoldGeneral()->getOwner()->getMoney()+city[currentCity].getCrossFee()*2);
                    if(player[whoseTurn].getMoney()<=0){
                    corrupt();
                    }
                }
                break;
            }
        }
    }
    else if(state=="出战取消"){
        QMessageBox::about(NULL,city[currentCity].getCityName(),"出战取消"+ player[whoseTurn].getKingName()+"支付双倍("+QString::number(city[currentCity].getCrossFee()*2)+")过路费!");
        player[whoseTurn].setMoney(player[whoseTurn].getMoney()-city[currentCity].getCrossFee()*2);
        city[currentCity].getHoldGeneral()->getOwner()->setMoney(city[currentCity].getHoldGeneral()->getOwner()->getMoney()+city[currentCity].getCrossFee()*2);
        if(player[whoseTurn].getMoney()<=0){
            corrupt();
        }
    }
    else if(state=="更换"){
        for(int i=0;i<general.length();i++){
            if(general[i].getName()==generalName){
                general[i].setHoldCity(&city[currentCity]);
                city[currentCity].getHoldGeneral()->setHoldCity(NULL);
                city[currentCity].setHoldGeneral(&general[i]);
                break;
            }
        }
    }
    else if(state=="招募"){
        for(int i=0;i<general.length();i++){
            if(general[i].getName()==generalName){
                player[whoseTurn].addGeneral(&general[i]);
                general[i].setOwner(&player[whoseTurn]);
                player[whoseTurn].setMoney(player[whoseTurn].getMoney()-generalPrice);
                break;
            }
        }
    }
    finalStep();
}

void Board::getCasinoData(int money, QString state){
    if(state=="确认"){
        player[whoseTurn].setMoney(money);
    }
    finalStep();
}

void Board::occupiedCity(int index){
    if(player[whoseTurn].getRemainGeneral()==0){
        QMessageBox::about(NULL,city[index].getCityName(), "没有随行将军,无法占领该城市");
        finalStep();
    }
    else{
        if(player[whoseTurn].getMoney()>baseOccupiedMoney){
            QMessageBox message(QMessageBox::Question,city[index].getCityName(),"是否愿意花费"+QString::number(baseOccupiedMoney)+"元占领"+city[index].getCityName()+"?",QMessageBox::Yes|QMessageBox::No,NULL);
            message.setButtonText(QMessageBox::Yes,"占领");
            message.setButtonText(QMessageBox::No,"取消");
            if (message.exec()==QMessageBox::Yes)  {
                  QList<General*> gen=player[whoseTurn].getOwnedGeneral();
                  currentCity=index;
                  QStringList *allGeneral=new QStringList();
                  for(int i=0;i<gen.length();i++){
                      if(gen[i]->getHoldCity()==NULL){
                          allGeneral->append(gen[i]->getName());
                      }
                  }
                  SelectGeneral *select=new SelectGeneral(NULL,allGeneral,"守城");
                  select->show();
                  connect(select,SIGNAL(sendGeneral(QString,QString)),this,SLOT(getGeneralData(QString,QString)));
            }
            else{
                finalStep();
            }
        }
        else{
            QMessageBox::about(NULL,city[index].getCityName(), "金钱不足,无法占领该城市");
            finalStep();
        }
    }
}

void Board::upgradeCity(int index){
    if(player[whoseTurn].getMoney()>baseupgradeMoney+(city[index].getCityLevel()-1)*100){
        QMessageBox message(QMessageBox::Question,city[index].getCityName(),"是否愿意花费"+QString::number(baseupgradeMoney+(city[index].getCityLevel()-1)*100)+"元升级"+city[index].getCityName()+"?",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"升级");
        message.setButtonText(QMessageBox::No,"取消");
        if (message.exec()==QMessageBox::Yes)  {
            city[index].setCityLevel(city[index].getCityLevel()+1);
            city[index].setCrossFee(city[index].getCrossFee()*2);
            ui->checkBoard->setItem(city[index].getMarkX(),city[index].getMarkY(),new QTableWidgetItem(city[index].getHoldGeneral()->getOwner()->getKingName()+"("+QString::number(city[index].getCityLevel())+"级)"));
        }
    }
    else{
        QMessageBox::about(NULL,city[index].getCityName(), "金钱不足,无法升级该城市");
    }
    finalStep();
}

void Board::fightOrPay(int index){
    if(player[whoseTurn].getMoney()>city[index].getCrossFee()){
        QMessageBox message(QMessageBox::Question,city[index].getCityName(),"是否愿意交"+QString::number(city[index].getCrossFee())+"元过路费?",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"你是哥,我给钱");
        message.setButtonText(QMessageBox::No,"交个毛,干死你");
        int result=message.exec();
        if (result==QMessageBox::Yes)  {
            player[whoseTurn].setMoney(player[whoseTurn].getMoney()-city[index].getCrossFee());
            city[index].getHoldGeneral()->getOwner()->setMoney(city[index].getHoldGeneral()->getOwner()->getMoney()+city[index].getCrossFee());
            finalStep();
        }
        else if(result==QMessageBox::No){
            if(player[whoseTurn].getRemainGeneral()>0){
                fight(index);
            }
            else{
                QMessageBox::about(NULL,city[index].getCityName(), "没有随行将军,只能给钱");
                player[whoseTurn].setMoney(player[whoseTurn].getMoney()-city[index].getCrossFee());
                city[index].getHoldGeneral()->getOwner()->setMoney(city[index].getHoldGeneral()->getOwner()->getMoney()+city[index].getCrossFee());
                finalStep();
            }
        }
        else{
            finalStep();
        }
    }
    else{
        if(player[whoseTurn].getRemainGeneral()>0){
            QMessageBox::about(NULL,city[index].getCityName(), "金钱不足,只能战斗");
            fight(index);
        }
        else{
            finalStep();
        }
    }
}


void Board::fight(int index){
    QList<General*> gen=player[whoseTurn].getOwnedGeneral();
    currentCity=index;
    QStringList *allGeneral=new QStringList();
    for(int i=0;i<gen.length();i++){
        if(gen[i]->getHoldCity()==NULL){
            allGeneral->append(gen[i]->getName());
        }
    }
    SelectGeneral *select=new SelectGeneral(NULL,allGeneral,"出战");
    select->show();
    connect(select,SIGNAL(sendGeneral(QString,QString)),this,SLOT(getGeneralData(QString,QString)));
}

void Board::cityMove(){
    int index;
    for(index=0;index<city.length();index++){
        if(city[index].getCityName()==ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->text()){
            break;
        }
    }
    if(city[index].getHoldGeneral()==NULL){
        occupiedCity(index);
    }
    else if(city[index].getHoldGeneral()->getOwner()->getID()==player[whoseTurn].getID()){
        QMessageBox message(QMessageBox::Question,city[index].getCityName(),"如何选择?",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"升级城市");
        message.setButtonText(QMessageBox::No,"调换武将");
        int result=message.exec();
        if (result==QMessageBox::Yes)  {
            upgradeCity(index);
        }
        else if(result==QMessageBox::No){
            switchCityGeneral(index);
        }
        else{
            finalStep();
        }
    }
    else{
        fightOrPay(index);
    }
}

void Board::showMapInfo(int x, int y){
    if(ui->checkBoard->item(x,y)->text().contains("城")){
        for(int i=0;i<city.length();i++){
            if(city[i].getCityName()==ui->checkBoard->item(x,y)->text()){
                QString belongPlayer;
                QString belongGeneral;
                if(city[i].getHoldGeneral()==NULL){
                    belongGeneral="无";
                    belongPlayer="无";
                }
                else{
                    belongGeneral=city[i].getHoldGeneral()->getName();
                    belongPlayer=city[i].getHoldGeneral()->getOwner()->getKingName();
                }
                QMessageBox::about(NULL,"基本信息", city[i].getCityName()+"\n"+"城市等级: "+city[i].getCityLevel()+"\n"+"过路费: "+QString::number(city[i].getCrossFee())+"\n"+
                                   "占有者: "+belongPlayer+"\n"+"守城将军: "+belongGeneral);
            }
        }
    }
}

void Board::switchCityGeneral(int index){
    if(player[whoseTurn].getRemainGeneral()==0){
        QMessageBox::about(NULL,city[index].getCityName(), "没有可以调换的将军");
        finalStep();
    }
    else{
        QList<General*> gen=player[whoseTurn].getOwnedGeneral();
        currentCity=index;
        QStringList *allGeneral=new QStringList();
        for(int i=0;i<gen.length();i++){
            if(gen[i]->getHoldCity()==NULL){
                allGeneral->append(gen[i]->getName());
            }
        }
        SelectGeneral *select=new SelectGeneral(NULL,allGeneral,"更换");
        select->show();
        connect(select,SIGNAL(sendGeneral(QString,QString)),this,SLOT(getGeneralData(QString,QString)));
    }
}

void Board::afterMove(){
    if(ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->text().contains("城")){
        cityMove();
    }
    else if(ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->text()=="商店"){
        Shop *shop=new Shop(NULL,player[whoseTurn].getMoney());
        shop->show();
        connect(shop,SIGNAL(sendbuyList(QList<QString>,QList<int>,int)),this,SLOT(getbuyList(QList<QString>,QList<int>,int)));
    }
    else if(ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->text()=="酒馆"){
        if(player[whoseTurn].getMoney()>generalPrice){
            QStringList *availableGeneral=new QStringList();
            for(int i=0;i<general.length();i++){
                if(general[i].getOwner()==NULL){
                    availableGeneral->append(general[i].getName());
                }
            }
            SelectGeneral *select=new SelectGeneral(NULL,availableGeneral,generalPrice);
            select->show();
            connect(select,SIGNAL(sendGeneral(QString,QString)),this,SLOT(getGeneralData(QString,QString)));
        }
        else{
            QMessageBox::about(NULL,"酒馆", "没有足够的金钱招募将军");
        }
    }
    else if(ui->checkBoard->item(player[whoseTurn].getCurrentX(),player[whoseTurn].getCurrentY())->text()=="赌场"){
        Casino *cas=new Casino(NULL,player[whoseTurn].getMoney());
        cas->show();
        connect(cas,SIGNAL(sendCasino(int,QString)),this,SLOT(getCasinoData(int,QString)));

    }
    else{
        finalStep();
    }
}

void Board::on_quitGameBtn_clicked(){
    if(playerNum<2){
        this->close();
    }
    else{
        QMessageBox message(QMessageBox::Question,"退出游戏","确定要退出吗?",QMessageBox::Yes|QMessageBox::No,NULL);
        message.setButtonText(QMessageBox::Yes,"确定");
        message.setButtonText(QMessageBox::No,"取消");
        int result=message.exec();
        if (result==QMessageBox::Yes)  {
            this->close();
        }
    }
}

void Board::on_checkInfoBtn_clicked(){
    ShowInfo *info=new ShowInfo(NULL,&player);
    info->show();
}

void Board::on_useItemBtn_clicked(){
    UseItem *use=new UseItem(NULL,&player,whoseTurn);
    use->show();
}
