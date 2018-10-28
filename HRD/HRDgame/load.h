#pragma once
#include <QtWidgets/QMainWindow>
#include<QString>
#include <QStringList>


class load{
public:
    load();
    ~load();//;w;
    int loadName();//用户名和id
    int loadLevelNum();//已过关数
    int loadPBSN(int level);//最佳步数
    int loadBSN(int level);//每一关的最优解
    int loadChessBoard(int ChessBoard[5][4],int level);//棋盘
    static QStringList loadLevelName();//每一关的关卡名
    static void loadSolution(int Solution[50][5][4], int level, int stepnum);//从文件中加载解法演示


    int getPresLevel(){
        return presLevel_;
    }
    int getId(){return id_;}
    QString getName(){return name_;}
    int getLevelNum(){return levelNum_;}
    int getPBSN(){return pBestStepNum_;}
    int getBSN(){return bestStepNum_;}


private:
    QString name_;//player's name
    int presLevel_;//present level
    int levelNum_;//levels which have been passed
    int stepNum_;//present step number
    int pBestStepNum_;//personal best steps
    int bestStepNum_;//official solution step's number
    int id_;//user's code
    int level_;//用来判断用户玩哪一关
};
