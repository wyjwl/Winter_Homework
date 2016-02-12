#include "richest_in_the_world.h"
#include "ui_richest_in_the_world.h"
#include "introduction.h"
#include "initialize.h"
#include "board.h"

Richest_in_the_world::Richest_in_the_world(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Richest_in_the_world)
{
    ui->setupUi(this);
    this->setWindowTitle("富甲天下混搭大富翁_寒假作业");
    connect(ui->quitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
}

Richest_in_the_world::~Richest_in_the_world()
{
    delete ui;
}

void Richest_in_the_world::on_introductionBtn_clicked()
{
    Introduction *p=new Introduction();
    p->show();
}


void Richest_in_the_world::on_newGameBtn_clicked()
{
    Initialize *p=new Initialize();
    p->show();
}
