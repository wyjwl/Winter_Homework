#include "introduction.h"
#include "ui_introduction.h"

Introduction::Introduction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Introduction)
{
    ui->setupUi(this);
    this->setWindowTitle("游戏介绍");
}

Introduction::~Introduction()
{
    delete ui;
}
