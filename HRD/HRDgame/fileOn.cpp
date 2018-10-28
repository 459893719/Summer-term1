#include "fileOn.h"
#include<qfile.h>
#include<qtextstream.h>
#include<qiodevice.h>
#include<qstring.h>
#include<qmessagebox.h>
#include<qdebug.h>


fileOn::fileOn()
{
}


void fileOn::writeName(int id, QString name)//用户第一次玩时存储的用户名和id
{
    QString cnt_nid = QString::number(id) + " " + name;

    QFile file("./save/info_nid.txt"); //open the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "错误", "存档写入失败，请重新尝试。", "确定");
        return;
    }

    QTextStream out(&file);
    out << cnt_nid;//write
    file.close();
}

void fileOn::writeLevelNum(int levelNum)//已过关数单独文件
{

    QString cnt_LevelNum = QString::number(levelNum);

    //level = 0;一开始存成0，应该不是放这儿
    QFile file("./save/info_LevelNum.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "错误", "存档写入失败，请重新尝试。", "确定");
        return;
    }
    QTextStream out(&file);
    out << cnt_LevelNum;//write
    file.close();
}

void fileOn::writePBSN(int pBestStepNum, int level)//每一关的最佳步数
{
    QString cnt_pbsn = QString::number(pBestStepNum);
    QFile file("./save/info_pbsn" + QString::number(level) + ".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "错误", "存档写入失败，请重新尝试。", "确定");
        return;
    }
    QTextStream out(&file);
    out << cnt_pbsn;//write
    file.close();
}

void fileOn::writeBSN(int bestStepNum, int level)//每一关的最优解
{
    QString cnt_bsn = QString::number(bestStepNum);
    QFile file("./save/info_bsn" + QString::number(level) + ".txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(NULL, "错误", "存档写入失败，请重新尝试。", "确定");
        return;
    }
    QTextStream out(&file);
    out << cnt_bsn;//write
    file.close();
}
