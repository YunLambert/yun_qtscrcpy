#include "dialog.h"
#include "ui_dialog.h"
#include "adbprocess.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&m_server,&server::serverStartResult,this,[this](bool success){
        qDebug()<<"server start"<<success;
    });
    connect(&m_server,&server::connectToResult,this,[this](bool success,const QString& deviceName,const QSize& size){
        qDebug()<<"connectToResult"<<success<<deviceName<<size;
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    /*
    QStringList arguments;
    //arguments << "devices";
    arguments<<"shell";
    arguments<<"ip";
    arguments<<"-f";
    arguments<<"inet";
    arguments<<"addr";
    arguments<<"show";
    arguments<<"wlan0";

    AdbProcess *myProcess = new AdbProcess(this);
    connect(myProcess,&AdbProcess::adbProcessResult,this,[this,myProcess](AdbProcess::ADB_EXEC_RESULT processResult){
        qDebug()<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<processResult;
        if(AdbProcess::AER_SUCCESS_EXEC==processResult){
            //qDebug()<<myProcess->getDeviceSerialFromStdOut().join("*");
            qDebug()<<myProcess->getDeviceIPFromStdOut();
        }
    });
    //->push("","path1","path2");
    //->removePath("","path2");
    //->reverse("","scrcpy",5037);
    //->reverseRemove("","scrcpy");
    myProcess->execute("",arguments);
    */
    m_server.start("",27183,720,8000000);
}

void Dialog::on_pushButton_2_clicked()
{
    m_server.stop();
}
