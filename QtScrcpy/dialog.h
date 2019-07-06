#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"
#include "adbprocess.h"

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
    void on_startServerBtn_clicked();

    void on_stopServerBtn_clicked();

private:
    Ui::Dialog *ui;

    server m_server;
};

#endif // DIALOG_H
