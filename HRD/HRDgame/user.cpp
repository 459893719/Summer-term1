#include "user.h"

User::User()
{
    /*
    if (//打开文件失败）
    {
        //用read模式打开文件，若失败，当做初次游玩用户，提示输入用户名，并存档。
        levelNum_ = 0;
    }
    else
    {
        // 读取用户名，读取id
        // 读取用户已过关卡数
    }
    */
    pBestStepNum_ = 0;
}


void User::loadPbest(int presLevel, load fileLoad)
{
    //调用文件系统的读档，读取某关用户最佳步数。n为关数

    if(fileLoad.loadPBSN(presLevel)){
        pBestStepNum_ = fileLoad.getPBSN();
    }
    else{
        //读文件失败, 说明这一关用户没玩过, 因此设置值为0
        pBestStepNum_ = 0;
    }

}

bool User::compareStep(int stepNum_, int presLevel_)
{
    if (stepNum_ < pBestStepNum_ || pBestStepNum_ == 0)
    {
        pBestStepNum_ = stepNum_;

        //并将pBestStepNum_存档  还缺关数
        fileOn::writePBSN(pBestStepNum_, presLevel_);

        return true;
    }
    else{
        return false;
    }
}

void User::addlevelNum_()
{
    if (levelNum_ < 10)
    {
        levelNum_++;
        //并存入用户文件
        fileOn::writeLevelNum(levelNum_);

    }
}

User::~User()
{
}
