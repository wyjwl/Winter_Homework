#ifndef USEITEM_H
#define USEITEM_H

#include <QWidget>
#include "player.h"
#include "general.h"

namespace Ui {
class UseItem;
}

class UseItem : public QWidget
{
    Q_OBJECT

public:
    explicit UseItem(QWidget *parent = 0, QList<Player>* p=NULL, int cPlayer=0);
    ~UseItem();

    void initItemList();

    void updateItemList();

    void updateGeneralList();


private slots:
    void itemListClick();

    void on_useBtn_clicked();

private:
    Ui::UseItem *ui;
    int currentPlayer;
    QList<Player> *player;
};

#endif // USEITEM_H
