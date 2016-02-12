#include "initialize.h"
#include "ui_initialize.h"
#include "board.h"
#include <QMessageBox>

Initialize::Initialize(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Initialize)
{
    ui->setupUi(this);
    init();
    this->setWindowTitle("富甲天下混搭大富翁_寒假作业");
    connect(ui->quitBtn,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(ui->general1Table,SIGNAL(cellClicked(int,int)),this,SLOT(on_general1Table_selected(int,int)));
    connect(ui->general2Table,SIGNAL(cellClicked(int,int)),this,SLOT(on_general2Table_selected(int,int)));
    connect(ui->general3Table,SIGNAL(cellClicked(int,int)),this,SLOT(on_general3Table_selected(int,int)));
    connect(ui->player2Combo,SIGNAL(currentTextChanged(QString)),this,SLOT(resetCombo3()));
}

Initialize::~Initialize()
{
    delete ui;
}


void Initialize::on_playerNumberCombo_currentTextChanged()
{
    if(ui->playerNumberCombo->currentText()=="2"){
        hidePlayer3(true);
    }
    else{
        hidePlayer3(false);
    }
}

void Initialize::hidePlayer3(bool tag){
    if(tag){
        ui->label_5->hide();
        ui->label_8->hide();
        ui->player3Combo->hide();
        ui->general3Table->hide();
    }
    else{
        ui->label_5->show();
        ui->label_8->show();
        ui->player3Combo->show();
        ui->general3Table->show();
    }
}

void Initialize::initTable(){
    ui->general1Table->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->general1Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->general1Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->general2Table->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->general2Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->general2Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->general3Table->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->general3Table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->general3Table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Initialize::init(){
    this->setWindowTitle("初始设置");
    GENERAL_NUMBER=15;
    maxSelectGeneral=5;
    hidePlayer3(true);
    initGeneral();
    initTable();
}

void Initialize::initGeneral(){
    weiGeneral=new QStringList();
    shuGeneral=new QStringList();
    wuGeneral=new QStringList();
    allGeneral=new QStringList();
    weiGeneral->append("典韦");
    weiGeneral->append("许楮");
    weiGeneral->append("张辽");
    weiGeneral->append("夏侯敦");
    weiGeneral->append("庞德");
    weiGeneral->append("徐晃");
    weiGeneral->append("曹洪");
    weiGeneral->append("张合");
    weiGeneral->append("夏侯渊");
    weiGeneral->append("曹仁");
    weiGeneral->append("邓艾");
    weiGeneral->append("高览");
    weiGeneral->append("郝昭");
    weiGeneral->append("于禁");
    weiGeneral->append("曹休");
    shuGeneral->append("关羽");
    shuGeneral->append("张飞");
    shuGeneral->append("诸葛亮");
    shuGeneral->append("庞统");
    shuGeneral->append("徐庶");
    shuGeneral->append("赵云");
    shuGeneral->append("黄忠");
    shuGeneral->append("马超");
    shuGeneral->append("魏延");
    shuGeneral->append("姜维");
    shuGeneral->append("张苞");
    shuGeneral->append("关平");
    shuGeneral->append("法正");
    shuGeneral->append("黄月英");
    shuGeneral->append("关银屏");
    wuGeneral->append("黄盖");
    wuGeneral->append("韩当");
    wuGeneral->append("程普");
    wuGeneral->append("蒋钦");
    wuGeneral->append("周瑜");
    wuGeneral->append("鲁肃");
    wuGeneral->append("吕蒙");
    wuGeneral->append("陆逊");
    wuGeneral->append("太史慈");
    wuGeneral->append("甘宁");
    wuGeneral->append("周泰");
    wuGeneral->append("吴国太");
    wuGeneral->append("孙尚香");
    wuGeneral->append("大乔");
    wuGeneral->append("小乔");
    QStringList::Iterator iter=weiGeneral->begin();
    while(iter!=weiGeneral->end()){
        allGeneral->append(*iter++);
    }
    iter=shuGeneral->begin();
    while(iter!=shuGeneral->end()){
        allGeneral->append(*iter++);
    }
    iter=wuGeneral->begin();
    while(iter!=wuGeneral->end()){
        allGeneral->append(*iter++);
    }
    on_player1Combo_currentTextChanged();
    on_player2Combo_currentTextChanged();
    on_player3Combo_currentTextChanged();

}

void Initialize::on_player1Combo_currentTextChanged()
{
    ui->general1Table->clear();
    ui->general1Table->setRowCount(GENERAL_NUMBER);
    ui->general1Table->setColumnCount(2);
    QStringList::Iterator iter;
    if(ui->player1Combo->currentText()=="曹操"){
        iter=weiGeneral->begin();
    }
    else if(ui->player1Combo->currentText()=="刘备"){
        iter=shuGeneral->begin();
    }
    else{
        iter=wuGeneral->begin();
    }
    for(int i=0;i<GENERAL_NUMBER;i++){
        QTableWidgetItem *checkBox = new QTableWidgetItem();
        checkBox->setCheckState(Qt::Unchecked);
        ui->general1Table->setItem(i,0,checkBox);
        ui->general1Table->setItem(i,1,new QTableWidgetItem(*iter++));
    }
    resetCombo2();
}

void Initialize::resetCombo2(){
    ui->player2Combo->clear();
    ui->player2Combo->addItem("曹操");
    ui->player2Combo->addItem("刘备");
    ui->player2Combo->addItem("孙权");
    ui->player2Combo->removeItem(ui->player2Combo->findText(ui->player1Combo->currentText()));
    resetCombo3();
}

void Initialize::resetCombo3(){
    ui->player3Combo->clear();
    ui->player3Combo->addItem("曹操");
    ui->player3Combo->addItem("刘备");
    ui->player3Combo->addItem("孙权");
    ui->player3Combo->removeItem(ui->player3Combo->findText(ui->player1Combo->currentText()));
    ui->player3Combo->removeItem(ui->player3Combo->findText(ui->player2Combo->currentText()));
}

void Initialize::on_player2Combo_currentTextChanged()
{
    ui->general2Table->clear();
    ui->general2Table->setRowCount(GENERAL_NUMBER);
    ui->general2Table->setColumnCount(2);
    QStringList::Iterator iter;
    if(ui->player2Combo->currentText()=="曹操"){
        iter=weiGeneral->begin();
    }
    else if(ui->player2Combo->currentText()=="刘备"){
        iter=shuGeneral->begin();
    }
    else{
        iter=wuGeneral->begin();
    }
    for(int i=0;i<GENERAL_NUMBER;i++){
        QTableWidgetItem *checkBox = new QTableWidgetItem();
        checkBox->setCheckState(Qt::Unchecked);
        ui->general2Table->setItem(i,0,checkBox);
        ui->general2Table->setItem(i,1,new QTableWidgetItem(*iter++));
    }
}

void Initialize::on_player3Combo_currentTextChanged()
{
    ui->general3Table->clear();
    ui->general3Table->setRowCount(GENERAL_NUMBER);
    ui->general3Table->setColumnCount(2);
    QStringList::Iterator iter;
    if(ui->player3Combo->currentText()=="曹操"){
        iter=weiGeneral->begin();
    }
    else if(ui->player3Combo->currentText()=="刘备"){
        iter=shuGeneral->begin();
    }
    else{
        iter=wuGeneral->begin();
    }
    for(int i=0;i<GENERAL_NUMBER;i++){
        QTableWidgetItem *checkBox = new QTableWidgetItem();
        checkBox->setCheckState(Qt::Unchecked);
        ui->general3Table->setItem(i,0,checkBox);
        ui->general3Table->setItem(i,1,new QTableWidgetItem(*iter++));
    }
}

void Initialize::on_general1Table_selected(int row, int col){
    int selectNum=0;
    for(int i=0;i<ui->general1Table->rowCount();i++){
        if(ui->general1Table->item(i,0)->checkState()==Qt::Checked){
            selectNum++;
        }
    }
    if(ui->general1Table->item(row,0)->checkState()==Qt::Checked){
        ui->general1Table->item(row,0)->setCheckState(Qt::Unchecked);
    }
    else{
        if(selectNum<maxSelectGeneral){
            ui->general1Table->item(row,0)->setCheckState(Qt::Checked);
        }
    }
}

void Initialize::on_general2Table_selected(int row, int col){
    int selectNum=0;
    for(int i=0;i<ui->general2Table->rowCount();i++){
        if(ui->general2Table->item(i,0)->checkState()==Qt::Checked){
            selectNum++;
        }
    }
    if(ui->general2Table->item(row,0)->checkState()==Qt::Checked){
        ui->general2Table->item(row,0)->setCheckState(Qt::Unchecked);
    }
    else{
        if(selectNum<maxSelectGeneral){
            ui->general2Table->item(row,0)->setCheckState(Qt::Checked);
        }
    }
}

void Initialize::on_general3Table_selected(int row, int col){
    int selectNum=0;
    for(int i=0;i<ui->general3Table->rowCount();i++){
        if(ui->general3Table->item(i,0)->checkState()==Qt::Checked){
            selectNum++;
        }
    }
    if(ui->general3Table->item(row,0)->checkState()==Qt::Checked){
        ui->general3Table->item(row,0)->setCheckState(Qt::Unchecked);
    }
    else{
        if(selectNum<maxSelectGeneral){
            ui->general3Table->item(row,0)->setCheckState(Qt::Checked);
        }
    }
}

void Initialize::on_startBtn_clicked()
{
    int i;
    QStringList *gameInfo=new QStringList();
    gameInfo->append(ui->playerNumberCombo->currentText());
    gameInfo->append(ui->initialMoneyEdit->text());
    gameInfo->append("玩家1");
    gameInfo->append(ui->player1Combo->currentText());
    for(i=0;i<ui->general1Table->rowCount();i++){
        if(ui->general1Table->item(i,0)->checkState()==Qt::Checked){
            gameInfo->append(ui->general1Table->item(i,1)->text());
            allGeneral->removeAt(allGeneral->indexOf(ui->general1Table->item(i,1)->text()));
        }
    }
    gameInfo->append("玩家2");
    gameInfo->append(ui->player2Combo->currentText());
    for(i=0;i<ui->general2Table->rowCount();i++){
        if(ui->general2Table->item(i,0)->checkState()==Qt::Checked){
            gameInfo->append(ui->general2Table->item(i,1)->text());
            allGeneral->removeAt(allGeneral->indexOf(ui->general1Table->item(i,1)->text()));
        }
    }
    if(ui->playerNumberCombo->currentText()=="3"){
        gameInfo->append("玩家3");
        gameInfo->append(ui->player3Combo->currentText());
        for(i=0;i<ui->general3Table->rowCount();i++){
            if(ui->general3Table->item(i,0)->checkState()==Qt::Checked){
                gameInfo->append(ui->general3Table->item(i,1)->text());
                allGeneral->removeAt(allGeneral->indexOf(ui->general1Table->item(i,1)->text()));
            }
        }
    }
    gameInfo->append("闲置将军");
    QStringList::Iterator iter=allGeneral->begin();
    while(iter!=allGeneral->end()){
        gameInfo->append(*iter++);
    }
    Board *p=new Board(NULL,gameInfo);
    p->show();
    this->close();
}
