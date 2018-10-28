#ifndef HELP_H
#define HELP_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class Help;
}

class Help : public QMainWindow
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = 0);
    ~Help();

signals:
    void sendsignal();

private slots:
    void on_btn_return_clicked();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Help *ui;
};

#endif // HELP_H
