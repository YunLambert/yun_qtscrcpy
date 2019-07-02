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

void Dialog::on_pushButton_clicked()  //测试代码部分
{
    qDebug()<<QCoreApplication::applicationDirPath();
    QStringList arguments;
    arguments << "devices";

    AdbProcess *myProcess = new AdbProcess(this);
    //myProcess->start(AdbProcess::getAdbPath(),Q_NULLPTR);
    connect(myProcess, &AdbProcess::adbProcessResult,this,[this, myProcess](AdbProcess::ADB_EXEC_RESULT processResult){
        qDebug()<<">>>>>>>>>>"<<processResult;
        if (processResult == AdbProcess::AER_SUCCESS_EXEC)
        {
            qDebug()<<myProcess->getDevicesSerialFromStdOut().join("*");
        }
    });
    //test 启动：myProcess->execute("", arguments);
    //test push: myProcess->push("", "C:\\Users\\Administrator\\Desktop\\test.txt", "/sdcard/test.txt");
    //test removePath: myProcess->removePath("", "/sdcard/test.txt");
    //test reverse: myProcess->reverse("", "scrcpy", 5037);
    //test reverseremove: myProcess->reverseRemove("", "scrcpy");
    myProcess->execute("", arguments);
}
