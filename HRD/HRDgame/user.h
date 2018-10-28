#ifndef USER_H
#define USER_H

#endif // USER_H


#include <Qstring>
#include "load.h"
#include "fileOn.h"



/*
需要的功能：
用户已过关数，用户名，用户某关最佳步数，id
读取用户某关最佳步数（参数为当前关卡数）
读取用户名和id
构造函数里读取name和id
最佳步数判断

*/

class load;

class User
{
private:
    QString name_;
    int id_;
    int levelNum_;//levels which have been passed
    int pBestStepNum_;//personal best steps
public:
    User();
    QString getname() { return name_; }  //返回用户名
    int getId(){return id_;}
    int getlevelNum() { return levelNum_; }   //返回用户已过关卡数
    int getpBestStepNum_() { return pBestStepNum_; }   //返回用户某关最佳步数（未过关为0）
    void addlevelNum_();                               //过关时判断用户已过关数，进行自增和存档更新
    void loadPbest(int presLevel, load fileLoad);  //根据当前关卡数读取用户某关最佳步数
    bool compareStep(int stepNum_,int presLevel_);             //判断当前步数与最佳步数，并进行替换（在过关后判断）

    void setPBSN(int pbsn){
        pBestStepNum_ = pbsn;
    }
    void setId(int id){
        this->id_ = id;
    }
    void setName(QString name){
        name_ = name;
    }
    void setLevelNum(int levelnum){
        levelNum_ = levelnum;
    }

    ~User();
};
