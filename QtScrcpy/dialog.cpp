#include "dialog.h"
#include "ui_dialog.h"
#include<QProcess>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString program = "notepad";
    QStringList arguments;
    arguments << "-style" << "fusion";

    QProcess *myProcess = new QProcess(this);
   //myProcess->start(program, arguments);
    myProcess->start(program,Q_NULLPTR);
}
