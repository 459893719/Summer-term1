#ifndef SOLUTION_H
#define SOLUTION_H

#include <QMainWindow>
#include "load.h"
#include <QString>

class Level;

namespace Ui {
class Solution;
}

class Solution : public QMainWindow
{
    Q_OBJECT

public:
    explicit Solution(int preslevel, Level* level, QString levelName, QWidget *parent = 0);
    ~Solution();

private slots:
    void on_btn_lastStep_clicked();

    void on_btn_nextStep_clicked();

    void on_btn_back_clicked();

private:
    Ui::Solution *ui;
    Level* level;

    int presLevel;    //当前关卡
    int stepNum;      //最优步数
    int step;         //临时变量, 表示正在第几步
    int solution[50][5][4]; //存解法所有棋盘状态
    QString levelName;  //关名

signals:
    void sendsignal2();


protected:
    void paintEvent(QPaintEvent *);
};

#endif // SOLUTION_H
