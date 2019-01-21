#include "dialog.h"
#include "ui_dialog.h"
#include "adbprocess.h"
#include <QDebug>

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
    connect(myProcess,&AdbProcess::adbProcessResult,this,[this](AdbProcess::ADB_EXEC_RESULT processResult){
        qDebug()<<">>>>>>>>>>"<<processResult;
    });
    myProcess->reverseRemove("","scrcpy");
}
