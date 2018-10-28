#ifndef LEVEL_H
#define LEVEL_H

#endif // LEVEL_H
#include "chess.h"
#include <QPainter>
#include <QMediaPlayer>
#include <QSound>
#include <QMainWindow>

class Level
{
private:
    int chessboard[5][4]; //游戏界面中棋盘的抽象形式
    int bestStepNum_;//official solution step's number

    //——————棋子们—————————
    Chess* Caocao;
    Chess* Guanyu;
    Chess* Machao;
    Chess* Zhaoyun;
    Chess* Huangzhong;
    Chess* Zhangfei;
    Chess* Zu1;
    Chess* Zu2;
    Chess* Zu3;
    Chess* Zu4;
    //——————————————————

    QMediaPlayer* player;
    QMediaPlayer* player1;
    QMediaPlayer* player2;
    int Mflag;  //是否播放音效
    int flag;  //移动成功判断标志
    int musicPlay;

public:
    Level();
    void loadChessboard(int level);   //根据当前关卡数读取关卡对应棋盘
    void searchChessboard(QMainWindow* x);              //遍历棋盘，确定每个棋子坐标，给棋子赋值
    void resetChessboard(int preslevel,QMainWindow* x);  //重置棋盘
    void setChessboard(int ChessBoard[5][4]);   //装填棋盘
    void showSolution();                  //解法演示
    bool isClear();                       //判断是否过关
    int getChessboard(int qx,int qy);    //获取棋盘某一位置的状态
    int move(int id, char ch);           //根据棋子标号和输入信息进行棋子移动
    void paintQ(QMainWindow* x);
    void paintF(QMainWindow* x,int nowChess);
    void clickSound();

    int getBSN(){
        return bestStepNum_;
    }
    void setBSN(int bsn){bestStepNum_ = bsn;}

    ~Level();
};
