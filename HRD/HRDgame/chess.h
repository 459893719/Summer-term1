#ifndef CHESS_H
#define CHESS_H

#endif // CHESS_H
#include <QPainter>
#include <QLabel>
#include <QMainWindow>

class Chess {
private:
    int chess;      //棋子代号；
    int hori;      //棋子横向占格；
    int vert;       //棋子竖向占格；
    int qx;        //棋子横坐标；         横纵坐标优先选择“左和上”
    int qy;        //棋子纵坐标；
    QLabel* picLabel;  //棋子图片位置
    QPixmap pix;
    QPixmap frame;     //选中框,0非选中，1选中
public:
    Chess();   //基本用不到
    Chess(int chess, int hori, int vert, int qx, int qy,QMainWindow* x);   //初始化棋子（用关卡数据进行初始化）
    int getqx() { return qx; }   //获取棋子当前横坐标
    int getqy() { return qy; }   //获取棋子当前纵坐标
    int getchess() { return chess; }    //获取棋子代号
    int moveChess(char ch,int chessboard[5][4]); //棋子内核的移动，用于level中move函数
    QLabel* getQLabel();
    QPixmap getPixmap();
    QPixmap getFrame();
    ~Chess();
};
