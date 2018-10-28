#ifndef GAME_H
#define GAME_H

#endif // GAME_H

#include "user.h"
#include "level.h"
#include "bgm.h"
#include "client.h"

class Game
{
private:
    int presLevel_;//当前关卡
    int stepNum_;//当前步数
    int Qx;  //光标横坐标
    int Qy;  //光标纵坐标
    int nowChess;   //光标位置的数组棋盘元素

    User* user_;
    Level* level_;
    Bgm* bgm_;
    Client* client_;

    //BGM和音效对象
public:
    Game();
    int getstepNum() { return stepNum_; }   //获取当前步数
    int getpresLevel() { return presLevel_; }  //获取当前关卡
    int getQx() { return Qx; }  //获取光标横坐标
    int getQy() { return Qy; }  //获取光标纵坐标
    void setQ(int x,int y);
    void setnowChess(int i);
    void moveStep();  //步数自增
    void reChessboard(QMainWindow* x);    //重置棋盘
    void setBGM(bool signal);      //bgm开关
    void setSound(bool signal);    //音效开关
    int levelClear(QMainWindow* x);   //过关
    void nextLevel(QMainWindow* x);
    Level* getlevel();
    User* getuser(){return user_;}
    Client* getClient(){return client_;}
    int getnowChess();

    void setPresLevel(int presLevel){
        presLevel_ = presLevel;
    }
    void setStepNum(int stepNum){ stepNum_ = stepNum; }
    void setClient(Client* client){
        client_ = client;
    }
    Bgm* getBgm(){return bgm_;}
    ~Game();
};
