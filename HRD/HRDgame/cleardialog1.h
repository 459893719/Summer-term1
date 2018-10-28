#ifndef CLEARDIALOG1_H
#define CLEARDIALOG1_H

#include <QDialog>

namespace Ui {
class clearDialog1;
}

class clearDialog1 : public QDialog
{
    Q_OBJECT

public:
    explicit clearDialog1(QWidget *parent = 0);
    ~clearDialog1();

private slots:
    void on_btn_ok_clicked();

private:
    Ui::clearDialog1 *ui;
};

#endif // CLEARDIALOG1_H
