#include "selectgeneral.h"
#include "ui_selectgeneral.h"
#include <QTime>


SelectGeneral::SelectGeneral(QWidget *parent, QStringList *general, QString s) :
    QWidget(parent),
    ui(new Ui::SelectGeneral)
{
    ui->setupUi(this);
    QStringList::Iterator iter=general->begin();
    while(iter!=general->end()){
        ui->generalCombo->addItem(*iter++);
    }
    state=s;
    generalPrice=0;
    this->setWindowTitle("请选择"+s+"的将军");
    ui->label->setText("请选择"+s+"的将军");
    ui->confirm->setText("确认");
}

SelectGeneral::SelectGeneral(QWidget *parent, QStringList *general, int price) :
    QWidget(parent),
    ui(new Ui::SelectGeneral)
{
    ui->setupUi(this);
    state="招募";
    this->setWindowTitle("招募将军");
    ui->label->setText("您可以花费"+QString::number(price)+"来招募以下一位将军");
    ui->confirm->setText("招募");
    setRandom();
    int index;
    int tryTimes=3;
    while(tryTimes!=0){
        index=qrand()%(general->length()-1);
        ui->generalCombo->addItem(general->value(index));
        general->removeAt(index);
        tryTimes--;
    }
}


SelectGeneral::~SelectGeneral()
{
    delete ui;
}

void SelectGeneral::closeEvent(QCloseEvent *e){
    if(state=="守城"){
        emit sendGeneral(ui->generalCombo->currentText(),"关闭");
    }
    else if(state=="出战"){
        emit sendGeneral(ui->generalCombo->currentText(),state+"取消");
    }
    else if(state=="招募"){
        emit sendGeneral(ui->generalCombo->currentText(),"关闭");
    }
}

void SelectGeneral::setRandom(){
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
}

void SelectGeneral::on_confirm_clicked()
{
    emit sendGeneral(ui->generalCombo->currentText(),state);
    blockSignals(true);
    this->close();
}


