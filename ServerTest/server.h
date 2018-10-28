#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QNetworkInterface>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>

/*Server类
 * 实现服务器的搭建, 并能根据客户端需求执行数据库操作
 */

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;
    QTcpServer* tcpServer;
    QList<QTcpSocket*> tcpClient;
    QTcpSocket* currentClient;


public slots:
    void NewConnectionSlot();
    void disconnectedSlot();
    void ReadAndSendData();
    void ConnectDB();



private slots:
    void on_btn_connect_clicked();
};

#endif // SERVER_H
