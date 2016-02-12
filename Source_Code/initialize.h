#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QWidget>
#include <QString>
#include <QListView>

namespace Ui {
class Initialize;
}

class Initialize : public QWidget
{
    Q_OBJECT

public:
    explicit Initialize(QWidget *parent = 0);

    ~Initialize();

    void hidePlayer3(bool tag);

    void initialPlayerRole();

    void init();

    void initGeneral();

    void initTable();


private slots:

    void on_playerNumberCombo_currentTextChanged();

    void on_player1Combo_currentTextChanged();

    void on_player2Combo_currentTextChanged();

    void on_player3Combo_currentTextChanged();

    void on_general1Table_selected(int row, int col);

    void on_general2Table_selected(int row, int col);

    void on_general3Table_selected(int row, int col);

    void on_startBtn_clicked();

    void resetCombo2();

    void resetCombo3();

private:
    Ui::Initialize *ui;
    QStringList *weiGeneral;
    QStringList *shuGeneral;
    QStringList *wuGeneral;
    QStringList *allGeneral;
    int GENERAL_NUMBER;
    int maxSelectGeneral;

};

#endif // INITIALIZE_H
