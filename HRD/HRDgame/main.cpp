#include <QApplication>
#include "widget.h"
#include"warn.h"
#include <QDebug>
#include "menu.h"
#include "load.h"
#include "client.h"
#include "login.h"
#include <QDir>
#include <QMessageBox>
#include <QMutex>
#include <QWaitCondition>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client* client = new Client();

    Warn* warn = new Warn();
    warn->exec();

    load fileLoad;

    if(!fileLoad.loadName()){
        //用户第一次玩游戏, 弹出登录界面
        Login* r = new Login(client);
        r->exec();
    }
    //否则就不弹出登录界面, 直接打开主菜单
    Menu* w = new Menu(client);
    w->show();

    return a.exec();
}
