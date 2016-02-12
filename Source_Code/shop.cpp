#include "shop.h"
#include "ui_shop.h"

Shop::Shop(QWidget *parent, int money) :
    QWidget(parent),
    ui(new Ui::Shop)
{
    ui->setupUi(this);
    for(int i=0;i<ui->itemCombo->count();i++){
        itemPrice.insert(ui->itemCombo->itemText(i),100*(i+1));
    }
    this->setWindowTitle("三国大超市");
    ui->remainMoneyEdit->setText(QString::number(money));
    connect(ui->itemCombo,SIGNAL(currentTextChanged(QString)),this,SLOT(enableBuyBtn()));
    connect(ui->itemNumber,SIGNAL(valueChanged(int)),this,SLOT(enableBuyBtn()));
}

Shop::~Shop()
{
    delete ui;
}

void Shop::closeEvent(QCloseEvent *e){
    emit sendbuyList(buyList,buyNum,ui->remainMoneyEdit->text().toInt());
}

void Shop::enableBuyBtn(){
    QMap<QString,int>::Iterator iter=itemPrice.find(ui->itemCombo->currentText());
    if(ui->remainMoneyEdit->text().toInt()<iter.value()*ui->itemNumber->text().toInt()){
        ui->buyBtn->setEnabled(false);
    }
    else{
        ui->buyBtn->setEnabled(true);
    }
}

void Shop::on_buyBtn_clicked(){
    if(ui->itemNumber->text().toInt()>0){
        QMap<QString,int>::Iterator iter=itemPrice.find(ui->itemCombo->currentText());
        buyList.append(iter.key());
        buyNum.append(ui->itemNumber->text().toInt());
        ui->remainMoneyEdit->setText(QString::number(ui->remainMoneyEdit->text().toInt()-iter.value()*ui->itemNumber->text().toInt()));
        enableBuyBtn();
    }
}

void Shop::on_exitBtn_clicked()
{
    emit sendbuyList(buyList,buyNum,ui->remainMoneyEdit->text().toInt());
    blockSignals(true);
    this->close();
}
