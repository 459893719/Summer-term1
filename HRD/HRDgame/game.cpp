#include "game.h"
#include <iostream>
#include <conio.h>

#include <QMessageBox>
#include "load.h"

Game::Game()
{
    presLevel_ = 1;//present level
    stepNum_ = 0;//present step number
    Qx = 0;  //光标位置（用来接收鼠标坐标）
    Qy = 0;
    nowChess = 0;
    level_=new Level();
    user_=new User();
    bgm_ = new Bgm();
}


Game::~Game()
{
}



void Game::moveStep()
{
    stepNum_++;
}

int Game::levelClear(QMainWindow* x)
{
    if(level_->isClear()){
        bool isBreakRecord = user_->compareStep(stepNum_, presLevel_);  //将这两步放在最前边，避免下面关卡变动时出现存储位置错误。
        stepNum_ = 0;

        //判断用户是否是第一次通过这一关
        if (presLevel_ > user_->getlevelNum())
        {
            user_->addlevelNum_();
            //如果是, 刷新过关记录, 并向服务器发3号指令和2号指令
           /* client_->sendAndRecv("2 " + QString::number(user_->getId()) + " " + QString::number(user_->getlevelNum()));
            client_->sendAndRecv("3 level" + QString::number(presLevel_) + " " +
                                 QString::number(user_->getId()) + " " +
                                 user_->getname() + " " +
                                 QString::number(user_->getpBestStepNum_()));*/
        }
        else{
            if(isBreakRecord){
                //向服务器发4号指令

               /* client_->sendAndRecv("4 level" + QString::number(presLevel_) + " " +
                                     QString::number(user_->getId()) + " " +
                                     QString::number(user_->getpBestStepNum_()));*/
            }

        }
        //以上是通用的过关后操作
        if(presLevel_ < 10){
            return 1;
        }
        else{
            return 2;
        }
    }
    else{
        return 0;
    }


}

void Game::nextLevel(QMainWindow* x)
{
        presLevel_++;
        level_->loadChessboard(presLevel_);
        level_->searchChessboard(x);
        load fileLoad;
        user_->loadPbest(presLevel_, fileLoad);

        fileLoad.loadBSN(presLevel_);
        level_->setBSN(fileLoad.getBSN());



        //根据当前关卡变量值读取对应棋盘，对应棋盘最优步数，对应棋盘玩家最佳步数。
        //进入下一关
}

void Game::reChessboard(QMainWindow* x)
{
    stepNum_ = 0;
    level_->resetChessboard(presLevel_,x);
}


void Game::setQ(int x,int y)
{
    Qx=x;
    Qy=y;
}

Level* Game::getlevel()
{
    return level_;
}

void Game::setnowChess(int i)
{
    nowChess=i;
}

int Game::getnowChess()
{
    return nowChess;
}
