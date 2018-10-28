#ifndef WARN_H
#define WARN_H

#include <QDialog>
#include <QTimer>
#include <QMouseEvent>


namespace Ui {
class Warn;
}

class Warn : public QDialog
{
    Q_OBJECT

public:
    explicit Warn(QWidget *parent = 0);
    ~Warn();

private:
    Ui::Warn *ui;

    // 鼠标按下
    void mousePressEvent(QMouseEvent * event) ;

private slots:

};

#endif // WARN_H
