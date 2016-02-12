#include "useitem.h"
#include "ui_useitem.h"
#include <QMessageBox>

UseItem::UseItem(QWidget *parent, QList<Player> *p, int cPlayer) :
    QWidget(parent),
    ui(new Ui::UseItem)
{
    ui->setupUi(this);
    currentPlayer=cPlayer;
    player=p;
    this->setWindowTitle((*player)[currentPlayer].getKingName()+"的道具栏");
    initItemList();
    connect(ui->itemTable,SIGNAL(cellClicked(int,int)),this,SLOT(itemListClick()));

}

UseItem::~UseItem()
{
    delete ui;
}

void UseItem::initItemList(){
    ui->itemTable->setColumnCount(2);
    ui->useToWhomList->hide();
    ui->selectLabel->setText("请输入你想到摇到的点数:");
    ui->selectLabel->hide();
    ui->selectSpinBox->hide();
    ui->itemTable->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->itemTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->itemTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->itemTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->itemTable->setColumnWidth(0,250);
    updateItemList();
}

void UseItem::updateItemList(){
    ui->itemTable->setRowCount(0);
    ui->itemTable->setColumnCount(2);
    QMapIterator<QString,int> iter((*(*player)[currentPlayer].getAllItem()));
    while(iter.hasNext()){
        iter.next();
        ui->itemTable->setRowCount(ui->itemTable->rowCount()+1);
        ui->itemTable->setItem(ui->itemTable->rowCount()-1,0,new QTableWidgetItem(iter.key()));
        ui->itemTable->setItem(ui->itemTable->rowCount()-1,1,new QTableWidgetItem(QString::number(iter.value())));
    }
}

void UseItem::updateGeneralList(){
    ui->useToWhomList->clear();
    for(int i=0;i<(*player)[currentPlayer].getOwnedGeneral().length();i++){
        ui->useToWhomList->addItem((*player)[currentPlayer].getOwnedGeneral()[i]->getName()+"(当前武器:"+
                                   (*player)[currentPlayer].getOwnedGeneral()[i]->getWeapon()+")攻击力:"+QString::number((*player)[currentPlayer].getOwnedGeneral()[i]->getTotalAttack()));
    }

}

void UseItem::itemListClick(){
    if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text().contains("攻击力")){
        ui->useToWhomList->clear();
        ui->useToWhomList->show();
        ui->selectLabel->hide();
        ui->selectSpinBox->hide();
        updateGeneralList();
    }
    else if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()=="遥控卡"){
        ui->selectLabel->show();
        ui->selectSpinBox->show();
        ui->useToWhomList->addItem("123123");
        ui->useToWhomList->hide();
    }

    else{
        ui->selectLabel->hide();
        ui->selectSpinBox->hide();
        ui->useToWhomList->clear();
        ui->useToWhomList->show();
        for(int i=0;i<(*player).length();i++){
            ui->useToWhomList->addItem((*player)[i].getKingName());
        }
    }
}

void UseItem::on_useBtn_clicked(){
    if(ui->itemTable->currentRow()>=0 &&ui->useToWhomList->currentRow()>=0){
        if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text().contains("攻击力")){
            if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text().contains("剑")){
                QString originWeapon;
                for(int i=0;i<(*player)[currentPlayer].getOwnedGeneral().length();i++){
                    if(ui->useToWhomList->item(ui->useToWhomList->currentRow())->text().contains((*player)[currentPlayer].getOwnedGeneral()[i]->getName())){
                            originWeapon=(*player)[currentPlayer].getOwnedGeneral()[i]->getWeapon();
                            (*player)[currentPlayer].getOwnedGeneral()[i]->setWeapon(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                            if((*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()>1){
                               (*(*player)[currentPlayer].getAllItem()).insert(ui->itemTable->item(ui->itemTable->currentRow(),0)->text(),(*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()-1);
                            }
                            else{
                                (*(*player)[currentPlayer].getAllItem()).remove(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                            }
                            if(originWeapon!="无"){
                                if((*(*player)[currentPlayer].getAllItem()).find(originWeapon)==(*(*player)[currentPlayer].getAllItem()).end()){
                                    (*(*player)[currentPlayer].getAllItem()).insert(originWeapon,1);
                                }
                                else{
                                    (*(*player)[currentPlayer].getAllItem()).insert(originWeapon,(*(*player)[currentPlayer].getAllItem()).find(originWeapon).value()+1);
                                }
                            }
                            break;
                    }
                }
            }
            else{
                for(int i=0;i<(*player)[currentPlayer].getOwnedGeneral().length();i++){
                    if(ui->useToWhomList->item(ui->useToWhomList->currentRow())->text().contains((*player)[currentPlayer].getOwnedGeneral()[i]->getName())){
                            (*player)[currentPlayer].getOwnedGeneral()[i]->setAttack((*player)[currentPlayer].getOwnedGeneral()[i]->getSelfAttack()+1);
                            if((*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()>1){
                               (*(*player)[currentPlayer].getAllItem()).insert(ui->itemTable->item(ui->itemTable->currentRow(),0)->text(),(*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()-1);
                            }
                            else{
                                (*(*player)[currentPlayer].getAllItem()).remove(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                            }
                            break;
                    }
                }
            }
            updateGeneralList();
        }
        else{
            if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()=="反向卡"){
                for(int i=0;i<(*player).length();i++){
                    if((*player)[i].getKingName()==ui->useToWhomList->item(ui->useToWhomList->currentRow())->text()){
                       (*player)[i].reverseDirection();
                        if((*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()>1){
                           (*(*player)[currentPlayer].getAllItem()).insert(ui->itemTable->item(ui->itemTable->currentRow(),0)->text(),(*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()-1);
                        }
                        else{
                            (*(*player)[currentPlayer].getAllItem()).remove(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                        }
                        break;
                    }
                }
            }
            else if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()=="暂停卡"){
                for(int i=0;i<(*player).length();i++){
                    if((*player)[i].getKingName()==ui->useToWhomList->item(ui->useToWhomList->currentRow())->text()){
                       (*player)[i].setPauseState(true);
                        QMessageBox::about(NULL,"暂停卡",(*player)[currentPlayer].getKingName()+"对"+(*player)[i].getKingName()+"使用暂停卡" );
                        if((*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()>1){
                           (*(*player)[currentPlayer].getAllItem()).insert(ui->itemTable->item(ui->itemTable->currentRow(),0)->text(),(*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()-1);
                        }
                        else{
                            (*(*player)[currentPlayer].getAllItem()).remove(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                        }
                        break;
                    }
                }
            }
        }
        updateItemList();
    }
    else if(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()=="遥控卡"){
                (*player)[currentPlayer].setSelectNextMove(ui->selectSpinBox->text().toInt());
                if((*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()>1){
                   (*(*player)[currentPlayer].getAllItem()).insert(ui->itemTable->item(ui->itemTable->currentRow(),0)->text(),(*(*player)[currentPlayer].getAllItem()).find(ui->itemTable->item(ui->itemTable->currentRow(),0)->text()).value()-1);
                }
                else{
                    (*(*player)[currentPlayer].getAllItem()).remove(ui->itemTable->item(ui->itemTable->currentRow(),0)->text());
                }
                this->close();
            }
}
