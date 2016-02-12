#ifndef SHOWINFO_H
#define SHOWINFO_H

#include <QWidget>
#include "player.h"

namespace Ui {
class ShowInfo;
}

class ShowInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ShowInfo(QWidget *parent=NULL ,QList<Player>* player=NULL);
    ~ShowInfo();

    void setInfo(QList<Player> player);

private:
    Ui::ShowInfo *ui;
};

#endif // SHOWINFO_H
