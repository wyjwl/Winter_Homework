#include "casino.h"
#include "ui_casino.h"
#include <QMessageBox>
#include <QTime>

Casino::Casino(QWidget *parent, int max) :
    QWidget(parent),
    ui(new Ui::Casino)
{
    ui->setupUi(this);
    this->setWindowTitle("三国大赌场");
    maxMoney=max;
}

Casino::~Casino()
{
    emit sendCasino(maxMoney+ui->num->text().toInt(),"关闭");
    delete ui;
}

void Casino::closeEvent(QCloseEvent *e){
    emit sendCasino(maxMoney-ui->num->text().toInt(),"关闭");
}

void Casino::on_Btn_clicked()
{
    if(ui->num->text().toInt()>=maxMoney){
        QMessageBox::about(NULL,"别耍赖", "你没有那么多金钱");
    }
    else{
        setRandom();
        int result=qrand()%10+1;
        if(result>6){
           QMessageBox::about(NULL,"恭喜你", "获得"+QString::number(ui->num->text().toInt()*2));
           emit sendCasino(maxMoney+ui->num->text().toInt(),"确认");
        }
        else{
           QMessageBox::about(NULL,"下次再试试吧","啥都没有咯");
           emit sendCasino(maxMoney-ui->num->text().toInt(),"确认");
        }
        blockSignals(true);
        this->close();
    }
}

void Casino::setRandom(){
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
}
