#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "client.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(Client* client, QWidget *parent = 0);
    ~Login();

private:
    Ui::Login *ui;
    Client* client;


private slots:
    void on_btn_right_clicked();

};

#endif // LOGIN_H
