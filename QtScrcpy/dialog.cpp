#include "adbprocess.h"
#include <QDir>
#include "dialog.h"
#include "ui_dialog.h"
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
    qDebug()<<QCoreApplication::applicationDirPath();
    QStringList arguments;
    arguments << "";

    AdbProcess *myProcess = new AdbProcess(this);
    myProcess->start(AdbProcess::getAdbPath(),Q_NULLPTR);
}
