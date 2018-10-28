#include "solution.h"
#include "ui_solution.h"
#include "level.h"
#include <cstring>


Solution::Solution(int preslevel, Level* level, QString levelName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Solution)
{
    memset(solution, 0, sizeof(solution));
    this->presLevel = preslevel;
    this->level = new Level();

    this->level->loadChessboard(this->presLevel);
    this->level->searchChessboard(this);

    ui->setupUi(this);

    step = 0;

    //stepNum = this->level->getBSN();
    load fileLoad;
    fileLoad.loadBSN(preslevel);
    stepNum = fileLoad.getBSN();

    qDebug() << stepNum;

    load::loadSolution(solution, this->presLevel, stepNum);

    ui->num_best->display(stepNum);
    ui->lab_levelName->setText(levelName);

}

//将图片画在label
void Solution::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix1;
    pix1.load("./pic/背景.png");//图片的位置
    painter.drawPixmap(0,0,500,750,pix1);
    level->paintQ(this);
}

Solution::~Solution()
{
    delete ui;
}

void Solution::on_btn_lastStep_clicked()
{
    if(step != 0){
        step--;
        //加载上一步的棋盘
        level->setChessboard(solution[step]);
        level->searchChessboard(this);
        update();
    }

    if(step == 0){
        //此时棋盘在最开始的状态, 不能让用户再点击这个按钮了
        ui->btn_lastStep->setEnabled(false);
    }

    if(step != stepNum){
        ui->btn_nextStep->setEnabled(true);
    }
    ui->num_present->display(step);

}

void Solution::on_btn_nextStep_clicked()
{
    if(step != stepNum){
        step++;
        //加载下一步棋盘
        level->setChessboard(solution[step]);
        level->searchChessboard(this);
        update();
    }

    if(step == stepNum){
        //此时棋盘在最后的状态, 不能让用户再点击这个按钮了
        ui->btn_nextStep->setEnabled(false);
    }

    if(step != 0){
        ui->btn_lastStep->setEnabled(true);
    }
    ui->num_present->display(step);

}

void Solution::on_btn_back_clicked()
{
    emit sendsignal2();
    this->close();
}
