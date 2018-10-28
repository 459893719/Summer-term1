#include <fstream>
#include "level.h"
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

Level::Level()
{
     bestStepNum_ = 0;
     for(int i=0;i<5;i++)
     {
         for (int h=0;h<4;h++)
         {
             chessboard[i][h]=0;
         }
     }
     flag = 0;
     Mflag = 1;
     musicPlay=1;
     player = new QMediaPlayer;
     player->setMedia(QUrl::fromLocalFile("./bgm/sound_effect.mp3"));
     player->setVolume(30);
     player1 = new QMediaPlayer;
     player1->setMedia(QUrl::fromLocalFile("./bgm/sound_effect.mp3"));
     player1->setVolume(30);
     player2 = new QMediaPlayer;
     player2->setMedia(QUrl::fromLocalFile("./bgm/sound_effect.mp3"));
     player2->setVolume(30);
}




void Level::loadChessboard(int level)
{

    QFile File("./save/chessboard" + QString::number(level) + ".txt");
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "错误", "存档读取失败, 请重试.", "确定");
        return ;
    }
    QTextStream in1(&File);
    while (!in1.atEnd())
    {
        for(int r = 0; r < 5; r++){
            QString line = in1.readLine();
            QStringList list = line.split(" ");
            for(int i = 0; i < 4; i++){
                chessboard[r][i] = list[i].toInt();
            }
        }
    }

    File.close();
    return;
}


void Level::searchChessboard(QMainWindow* x)   //棋子定位
{
        for (int i = 4; i >= 0; i--)
        {
            for (int h = 3; h >= 0; h--)           //这里实际上，h为横坐标，i为纵坐标
            {
                switch (chessboard[i][h])
                {
                case 1:
                    Caocao = new Chess(1, 2, 2, h, i,x); break;
                case 2:
                    Guanyu = new Chess(2, 2, 1, h, i,x); break;
                case 3:
                    if (chessboard[i + 1][h] == 3)
                    {
                        Machao = new Chess(3, 1, 2, h, i,x);
                    }
                    else if (chessboard[i][h + 1] == 3)
                    {
                        Machao = new Chess(3, 2, 1, h, i,x);
                    }
                    break;
                case 4:
                    if (chessboard[i + 1][h] == 4)
                    {
                        Zhaoyun = new Chess(4, 1, 2, h, i,x);
                    }
                    else if (chessboard[i][h + 1] == 4)
                    {
                        Zhaoyun = new Chess(4, 2, 1, h, i,x);
                    }
                    break;
                case 5:
                    if (chessboard[i + 1][h] == 5)
                    {
                        Huangzhong = new Chess(5, 1, 2, h, i,x);
                    }
                    else if (chessboard[i][h + 1] == 5)
                    {
                        Huangzhong = new Chess(5, 2, 1, h, i,x);
                    }
                    break;
                case 6:
                    if (chessboard[i + 1][h] == 6)
                    {
                        Zhangfei = new Chess(6, 1, 2, h, i,x);
                    }
                    else if (chessboard[i][h + 1] == 6)
                    {
                        Zhangfei = new Chess(6, 2, 1, h, i,x);
                    }
                    break;
                case 7:
                    Zu1 = new Chess(7, 1, 1, h, i,x); break;
                case 8:
                    Zu2 = new Chess(8, 1, 1, h, i,x); break;
                case 9:
                    Zu3 = new Chess(9, 1, 1, h, i,x); break;
                case 10:
                    Zu4 = new Chess(10, 1, 1, h, i,x); break;
                }
            }
        }
}

Level::~Level()
{
    delete Caocao;
    delete Guanyu;
    delete Machao;
    delete Zhaoyun;
    delete Huangzhong;
    delete Zhangfei;
    delete Zu1;
    delete Zu2;
    delete Zu3;
    delete Zu4;
}

void Level::resetChessboard(int preslevel,QMainWindow* x)
{
    delete Caocao;
    delete Guanyu;
    delete Machao;
    delete Zhaoyun;
    delete Huangzhong;
    delete Zhangfei;
    delete Zu1;
    delete Zu2;
    delete Zu3;
    delete Zu4;
    loadChessboard(preslevel);
    searchChessboard(x);
}

void Level::showSolution()
{
    //留出，组员写
}

bool Level::isClear()
{
    if (Caocao->getqx() == 1 && Caocao->getqy() == 3)   //胜利判定
    {
        return true;
    }
    else
    {
        return false;
    }
}


int Level::move(int id, char ch){
    switch(id){
    case 1:flag = Caocao->moveChess(ch,chessboard); break;
    case 2:flag = Guanyu->moveChess(ch,chessboard); break;
    case 3:flag = Machao->moveChess(ch,chessboard); break;
    case 4:flag = Zhaoyun->moveChess(ch,chessboard); break;
    case 5:flag = Huangzhong->moveChess(ch,chessboard);break;
    case 6:flag = Zhangfei->moveChess(ch,chessboard); break;
    case 7:flag = Zu1->moveChess(ch,chessboard); break;
    case 8:flag = Zu2->moveChess(ch,chessboard); break;
    case 9:flag = Zu3->moveChess(ch,chessboard); break;
    case 10:flag = Zu4->moveChess(ch,chessboard); break;
    }

    if(Mflag==1)
        {
            if (flag == 1)
            {
                switch(musicPlay)
                {
                case 1:player->play();musicPlay++;break;
                case 2:player1->play();musicPlay++;break;
                case 3:player2->play();musicPlay=1;break;
                }
            }
        }
    return flag;
}

int Level::getChessboard(int qx,int qy)
{
   return chessboard[qy][qx];
}

void Level::paintQ(QMainWindow* x)
{
       QPainter painter(x);
       painter.drawPixmap(Caocao->getQLabel()->x(),Caocao->getQLabel()->y(),Caocao->getQLabel()->width(),Caocao->getQLabel()->height(),Caocao->getPixmap());
       painter.drawPixmap(Guanyu->getQLabel()->x(),Guanyu->getQLabel()->y(),Guanyu->getQLabel()->width(),Guanyu->getQLabel()->height(),Guanyu->getPixmap());
       painter.drawPixmap(Machao->getQLabel()->x(),Machao->getQLabel()->y(),Machao->getQLabel()->width(),Machao->getQLabel()->height(),Machao->getPixmap());
       painter.drawPixmap(Zhaoyun->getQLabel()->x(),Zhaoyun->getQLabel()->y(),Zhaoyun->getQLabel()->width(),Zhaoyun->getQLabel()->height(),Zhaoyun->getPixmap());
       painter.drawPixmap(Huangzhong->getQLabel()->x(),Huangzhong->getQLabel()->y(),Huangzhong->getQLabel()->width(),Huangzhong->getQLabel()->height(),Huangzhong->getPixmap());
       painter.drawPixmap(Zhangfei->getQLabel()->x(),Zhangfei->getQLabel()->y(),Zhangfei->getQLabel()->width(),Zhangfei->getQLabel()->height(),Zhangfei->getPixmap());
       painter.drawPixmap(Zu1->getQLabel()->x(),Zu1->getQLabel()->y(),Zu1->getQLabel()->width(),Zu1->getQLabel()->height(),Zu1->getPixmap());
       painter.drawPixmap(Zu2->getQLabel()->x(),Zu2->getQLabel()->y(),Zu2->getQLabel()->width(),Zu2->getQLabel()->height(),Zu2->getPixmap());
       painter.drawPixmap(Zu3->getQLabel()->x(),Zu3->getQLabel()->y(),Zu3->getQLabel()->width(),Zu3->getQLabel()->height(),Zu3->getPixmap());
       painter.drawPixmap(Zu4->getQLabel()->x(),Zu4->getQLabel()->y(),Zu4->getQLabel()->width(),Zu4->getQLabel()->height(),Zu4->getPixmap());

}


void Level::paintF(QMainWindow* x, int nowChess)
{
    QPainter painter(x);

    switch(nowChess){
    case 1: painter.drawPixmap(Caocao->getQLabel()->x(),Caocao->getQLabel()->y(),Caocao->getQLabel()->width(),Caocao->getQLabel()->height(),Caocao->getFrame()); break;
    case 2: painter.drawPixmap(Guanyu->getQLabel()->x(),Guanyu->getQLabel()->y(),Guanyu->getQLabel()->width(),Guanyu->getQLabel()->height(),Guanyu->getFrame()); break;
    case 3: painter.drawPixmap(Machao->getQLabel()->x(),Machao->getQLabel()->y(),Machao->getQLabel()->width(),Machao->getQLabel()->height(),Machao->getFrame()); break;
    case 4: painter.drawPixmap(Zhaoyun->getQLabel()->x(),Zhaoyun->getQLabel()->y(),Zhaoyun->getQLabel()->width(),Zhaoyun->getQLabel()->height(),Zhaoyun->getFrame()); break;
    case 5: painter.drawPixmap(Huangzhong->getQLabel()->x(),Huangzhong->getQLabel()->y(),Huangzhong->getQLabel()->width(),Huangzhong->getQLabel()->height(),Huangzhong->getFrame());break;
    case 6: painter.drawPixmap(Zhangfei->getQLabel()->x(),Zhangfei->getQLabel()->y(),Zhangfei->getQLabel()->width(),Zhangfei->getQLabel()->height(),Zhangfei->getFrame()); break;
    case 7: painter.drawPixmap(Zu1->getQLabel()->x(),Zu1->getQLabel()->y(),Zu1->getQLabel()->width(),Zu1->getQLabel()->height(),Zu1->getFrame());break;
    case 8: painter.drawPixmap(Zu2->getQLabel()->x(),Zu2->getQLabel()->y(),Zu2->getQLabel()->width(),Zu2->getQLabel()->height(),Zu2->getFrame());break;
    case 9: painter.drawPixmap(Zu3->getQLabel()->x(),Zu3->getQLabel()->y(),Zu3->getQLabel()->width(),Zu3->getQLabel()->height(),Zu3->getFrame());break;
    case 10:painter.drawPixmap(Zu4->getQLabel()->x(),Zu4->getQLabel()->y(),Zu4->getQLabel()->width(),Zu4->getQLabel()->height(),Zu4->getFrame());break;
    }
}

  void Level::clickSound()
  {
      if (Mflag==1)
      {
          Mflag=0;
      }
      else if(Mflag == 0)
      {
          Mflag=1;
      }
  }

  void Level::setChessboard(int ChessBoard[5][4])
  {
      for(int i=0; i<5; i++)
      {
          for (int h=0; h<4; h++)
          {
              chessboard[i][h]=ChessBoard[i][h];
          }
      }
  }
