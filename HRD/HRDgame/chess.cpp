#include "chess.h"



Chess::Chess()
{
    chess = 0;
    hori = 0;
    vert = 0;
    qx = 0;
    qy = 0;
}

Chess::Chess(int chess, int hori, int vert, int qx, int qy, QMainWindow* x)   //初始化棋子（用关卡数据进行初始化）
{
    this->chess = chess;
    this->hori = hori;
    this->vert = vert;
    this->qx = qx;
    this->qy = qy;
    picLabel  = new QLabel(x);
    picLabel -> setGeometry(qx*100+50,qy*100+150,hori*100,vert*100);   //棋子坐标和宽度设置完毕，偏移量已添加
    switch(chess)
    {
    case 1: pix.load("./pic/Caocao.png");break;//图片的位置
    case 2: pix.load("./pic/Guanyu.png");break;
    case 3:
        if(hori==2)
        {
            pix.load("./pic/Machao1.png");
        }
        else
        {
            pix.load("./pic/Machao2.png");
        }
        break;
    case 4:
        if(hori==2)
        {
            pix.load("./pic/Zhaoyun1.png");
        }
        else
        {
            pix.load("./pic/Zhaoyun2.png");
        }
        break;
    case 5:
        if(hori==2)
        {
            pix.load("./pic/Huangzhong1.png");
        }
        else
        {
            pix.load("./pic/Huangzhong2.png");
        }
        break;
    case 6:
        if(hori==2)
        {
            pix.load("./pic/Zhangfei1.png");
        }
        else
        {
            pix.load("./pic/Zhangfei2.png");
        }
        break;
    case 7:
    case 8:
    case 9:
    case 10: pix.load("./pic/Zu.png");break;
    }
    frame.load("./pic/frame.png");
}

int Chess::moveChess(char ch,int chessboard[5][4]){
    int flag = 0;
    switch(ch)
    {
    case 'W':
    case 'w':
        if (qy != 0)
        {
            if (chessboard[qy - 1][qx] == 0 && chessboard[qy - 1][qx + hori - 1] == 0)
            {
                chessboard[qy - 1][qx] = chess;
                chessboard[qy - 1][qx + hori - 1] = chess;
                chessboard[qy + vert - 1][qx] = 0;
                chessboard[qy + vert - 1][qx + hori - 1 ] = 0;
                qy--;  //改动A
                flag = 1;
            }
        }
        break;
    case 'A':
    case 'a':
        if (qx != 0)
        {
            if (chessboard[qy][qx - 1] == 0 && chessboard[getqy() + vert - 1][qx - 1] == 0)
            {
                chessboard[qy][qx - 1] = chess;
                chessboard[qy + vert - 1][qx - 1] = chess;
                chessboard[qy][qx + hori - 1] = 0;
                chessboard[qy + vert - 1][qx + hori - 1] = 0;
                qx--;
                flag = 1;
            }
        }
        break;
    case 'S':
    case 's':
        if ((qy + vert - 1) != 4)
        {
            if (chessboard[qy + vert][qx] == 0 && chessboard[qy + vert][qx + hori - 1] == 0)
            {
                chessboard[qy][qx] = 0;
                chessboard[qy][qx + hori - 1] = 0;
                chessboard[qy + vert][qx] = chess;
                chessboard[qy + vert][qx + hori - 1] = chess;
                qy++;
                flag = 1;
            }
        }
        break;
    case 'D':
    case 'd':
        if (qx + hori - 1 != 3)
        {
            if (chessboard[qy][qx + hori] == 0 && chessboard[qy + vert - 1][qx + hori] == 0)
            {
                chessboard[qy][qx + hori] = chess;
                chessboard[qy + vert - 1][qx + hori ] = chess;
                chessboard[qy][qx] = 0;
                chessboard[qy + vert - 1][qx] = 0;
                qx++;
                flag = 1;
            }
        }
        break;
    }
    picLabel->move(qx*100+50,qy*100+150);//向上移动就是x不变y减小
    return flag;
}


QLabel* Chess::getQLabel()
{
    return picLabel;
}

QPixmap Chess::getPixmap()
{
    return pix;
}

QPixmap Chess::getFrame()
{
    return frame;
}

Chess::~Chess()
{
}
