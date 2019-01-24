#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    server m_server;
};

#endif // DIALOG_H
