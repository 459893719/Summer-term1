#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(500, 500);
    picLabel = new QLabel(this);
    picLabel->setFixedSize(50, 50);

}
//将图片画在label
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load("D:/Qt/unitttts/untitled6/img/move.jpg");//图片的位置
    painter.drawPixmap(picLabel->x(),picLabel->y(),picLabel->width(),picLabel->height(),pix);
}

void Widget::keyPressEvent(QKeyEvent *event)
{

    int x = 0;
    int y = 0;
        switch (event->key()) {
        case Qt::Key_Up:
            y = picLabel->y() - 100;
            if(y > -10)
                picLabel->move(picLabel->x(), y);//向上移动就是x不变y减小
            break;
        case Qt::Key_Down:
            y = picLabel->y() + 100;
            if(y < this->height() - 40)
            {
                picLabel->move(picLabel->x(), y);//向下移动是x不变y 变大
            }
            break;
        case Qt::Key_Right:
            x = picLabel->x() + 100;
            if(x < this->width() - 40)
            {
                picLabel->move(x, picLabel->y());
            }
            break;
        case Qt::Key_Left:
            x = picLabel->x() - 100;
            if(x > -10)
                picLabel->move(x, picLabel->y());
            break;
        case Qt::Key_Escape:

            break;
        default:
            break;
        }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    int x=e->x();
    int y=e->y();
    //qDebug()<<x<<","<<y;
}

Widget::~Widget()
{

}
