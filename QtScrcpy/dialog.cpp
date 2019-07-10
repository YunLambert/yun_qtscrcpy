#include <QDir>
#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QBuffer>
#include "keycodes.h"
#include "input.h"
#include "controlevent.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&m_adb, &AdbProcess::adbProcessResult, this, [this](AdbProcess::ADB_EXEC_RESULT processResult){
        QString log="";
        bool newLine = true;
        switch (processResult)
        {
        case AdbProcess::AER_SUCCESS_EXEC:
            QStringList devices = m_adb.getDevicesSerialFromStdOut();
            if (!devices.isEmpty())
                ui->serialEdit->setText(devices.at(0));
            break;

        }

        if (!log.isEmpty())
        {
            outLog(log, newLine);
        }
    });
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::outLog(const QString &log, bool newLine)
{
    ui->outEdit->append(log);
    if (newLine)
        ui->outEdit->append("<br/>");
}

void Dialog::on_startServerBtn_clicked()  //测试代码部分
{
    /*QProcess封装adb
    qDebug()<<QCoreApplication::applicationDirPath();
    QStringList arguments;
    //arguments << "devices";
    arguments << "shell";
    arguments <<"ip";
    arguments <<"-f";
    arguments <<"inet";
    arguments <<"addr";
    arguments <<"show";
    arguments <<"wlan0";

    AdbProcess *myProcess = new AdbProcess(this);
    //myProcess->start(AdbProcess::getAdbPath(),Q_NULLPTR);
    connect(myProcess, &AdbProcess::adbProcessResult,this,[this, myProcess](AdbProcess::ADB_EXEC_RESULT processResult){
        qDebug()<<">>>>>>>>>>"<<processResult;
        if (processResult == AdbProcess::AER_SUCCESS_EXEC)
        {
           // qDebug()<<myProcess->getDevicesSerialFromStdOut().join("*");
            qDebug()<<myProcess->getDeviceIPFromStdOut();
        }
    });
    //test 启动：myProcess->execute("", arguments);
    //test push: myProcess->push("", "C:\\Users\\Administrator\\Desktop\\test.txt", "/sdcard/test.txt");
    //test removePath: myProcess->removePath("", "/sdcard/test.txt");
    //test reverse: myProcess->reverse("", "scrcpy", 5037);
    //test reverseremove: myProcess->reverseRemove("", "scrcpy");
    myProcess->execute("", arguments);
    */
    if (!m_videoForm) {
        m_videoForm = new VideoForm("");
    }
    m_videoForm->show();
//    m_server.start("",27183,720,8000000);
//    m_videoWidget->show();
}

void Dialog::on_stopServerBtn_clicked()
{
    if (m_videoForm)
        m_videoForm->close();
//    m_server.stop();
}

//void Dialog::on_touchButton_clicked()
//{
//    QByteArray byteArray;
//    QBuffer buffer(&byteArray);
//    buffer.open(QBuffer::WriteOnly);
//    //构造控制指令
//    buffer.putChar(2); //代表是一个mouse指令
//    buffer.putChar(AMOTION_EVENT_ACTION_DOWN); //mouse是一个按下指令
//    buffer.putChar(AMOTION_EVENT_BUTTON_PRIMARY >> 24);
//    buffer.putChar(AMOTION_EVENT_BUTTON_PRIMARY >> 16);
//    buffer.putChar(AMOTION_EVENT_BUTTON_PRIMARY >> 8);
//    buffer.putChar(AMOTION_EVENT_BUTTON_PRIMARY);

//    int x = 100;
//    buffer.putChar(x>>8);
//    buffer.putChar(x);

//    int y=200;
//    buffer.putChar(y>>8);
//    buffer.putChar(y);

//    buffer.putChar(m_videoWidget->frameSize().width() >> 8);
//    buffer.putChar(m_videoWidget->frameSize().width());
//    buffer.putChar(m_videoWidget->frameSize().height() >> 8);
//    buffer.putChar(m_videoWidget->frameSize().height());



//    buffer.close();
//}

void Dialog::on_updateDevice_clicked()
{
    outLog("update devices", false);
    m_adb.execute("",QStringList()<<"devices");

}
