#ifndef CLEARDIALOG_H
#define CLEARDIALOG_H

#include <QDialog>

namespace Ui {
class clearDialog;
}

class clearDialog : public QDialog
{
    Q_OBJECT

public:
    explicit clearDialog(QWidget *parent = 0);
    ~clearDialog();

private slots:
    void on_btn_next_clicked();



    void on_btn_cancel_clicked();

signals:
    void nextLevelSignal();

private:
    Ui::clearDialog *ui;
};

#endif // CLEARDIALOG_H
