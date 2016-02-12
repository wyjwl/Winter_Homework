#ifndef SHOP_H
#define SHOP_H

#include <QWidget>
#include <QMap>

namespace Ui {
class Shop;
}

class Shop : public QWidget
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = 0, int money=0);
    ~Shop();

    void closeEvent(QCloseEvent *e);

signals:
    void sendbuyList(QList<QString> buyList, QList<int> buyNum, int remainMoney);

private slots:
    void on_buyBtn_clicked();

    void enableBuyBtn();

    void on_exitBtn_clicked();

private:
    Ui::Shop *ui;
    QList<QString> buyList;
    QList<int> buyNum;
    QMap<QString,int> itemPrice;
};

#endif // SHOP_H
