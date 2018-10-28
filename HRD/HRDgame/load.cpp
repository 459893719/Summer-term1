#include "load.h"
#include<qfile.h>
#include<qtextstream.h>
#include<qiodevice.h>
#include<qstring.h>
#include<qmessagebox.h>
#include<qdebug.h>

load::load() {
}

int load::loadName()//用户名和id的文件读档
{
    QFile file("./save/info_nid.txt");
    QString loadString;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();//每次读取一行
        loadString.append(line);//追加
    }
    QStringList list = loadString.split(" ");
    QString idStr = list[0];
    id_ = idStr.toInt();
    name_ = list[1];
    file.close();
    return 1;
}

int load::loadLevelNum()//本地的已过关数
{
    QFile file("./save/info_LevelNum.txt");
    QString loadString;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();//每次读取一行
        loadString.append(line);//追加
    }
    levelNum_ = loadString.toInt();
    file.close();
    return 1;
}

int load::loadPBSN(int level)//每一关的最佳步数
{
    QFile file("./save/info_pbsn" + QString::number(level) + ".txt");
    QString loadString;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();//每次读取一行
        loadString.append(line);//追加
    }
    pBestStepNum_ = loadString.toInt();
    file.close();
    return 1;
}

int load::loadBSN(int level)//每一关的最优解
{
    QFile file("./save/info_bsn" + QString::number(level) + ".txt");
    QString loadString;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();//每次读取一行
        loadString.append(line);//追加
    }
    bestStepNum_ = loadString.toInt();
    file.close();
    return 1;
}

int load::loadChessBoard(int chessboard[5][4],int level)//棋盘
{
    QFile File("./save/chessboard" + QString::number(level) + ".txt");
    QString loadString1;
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
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
    return 1;
}

QStringList load::loadLevelName()//关卡名
{
    QFile file("./save/info_LevelName.txt");
    QStringList nameList;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return QStringList();//返回空字符串
    }

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString line = in.readLine();//每次读取一行
        nameList.append(line);
    }


    for(int i=0;i<nameList.size();i++){
        qDebug() << nameList[i];
    }

    return nameList;
}

void load::loadSolution(int Solution[50][5][4], int level, int stepnum){
    QFile File("./save/solution" + QString::number(level) + ".txt");
    if (!File.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return ;
    }
    QTextStream in1(&File);
    while (!in1.atEnd())
    {
        for(int r = 0; r < (stepnum + 1) * 5; r++){
            int step = r / 5;
            int row = r % 5;
            QString line = in1.readLine();
            QStringList list = line.split(" ");
            for(int col = 0; col < 4; col++){
                Solution[step][row][col] = list[col].toInt();
            }
        }
    }

    File.close();
}

load::~load(){

}
