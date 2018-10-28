#pragma once
#include <QtWidgets/QMainWindow>
#include <QString>
#include <QMessageBox>


class fileOn{
public:
    fileOn();
    static void writeName(int id, QString name);//用户第一次玩时存储的用户名和id
    static void writeLevelNum(int levelNum);//已过关数
    static void writePBSN(int pBestStepNum, int level);//每一关的最佳步数
    void writeBSN(int bestStepNum, int level);//每一关的最优解

};
