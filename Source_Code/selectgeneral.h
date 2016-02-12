#ifndef SELECTGENERAL_H
#define SELECTGENERAL_H

#include <QWidget>

namespace Ui {
class SelectGeneral;
}

class SelectGeneral : public QWidget
{
    Q_OBJECT

signals:
    void sendGeneral(QString name, QString state);

public:
    SelectGeneral(QWidget *parent = 0, QStringList *general=NULL, QString str="");
    SelectGeneral(QWidget *parent = 0, QStringList *general=NULL, int generalPrice=0);
    ~SelectGeneral();

    void closeEvent(QCloseEvent *e);

    void setRandom();


private slots:
    void on_confirm_clicked();


private:
    Ui::SelectGeneral *ui;
    QString state;
    int generalPrice;
};

#endif // SELECTGENERAL_H
