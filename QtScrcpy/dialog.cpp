#include "dialog.h"
#include "ui_dialog.h"
#include "adbprocess.h"

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
    QStringList arguments;
    arguments << "devices";

    AdbProcess *myProcess = new AdbProcess(this);
   //myProcess->start(program, arguments);
    myProcess->execute("",arguments);
}
