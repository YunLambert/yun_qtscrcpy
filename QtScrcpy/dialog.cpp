#include <QDir>
#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&m_server, &server::serverStartResult,this,[this](bool success){
        qDebug()<<"server start"<<success;
    });
    connect(&m_server, &server::connectToResult,this,[this](bool success, const QString& deviceName, const QSize& size){
        qDebug()<<"connectToResult"<<success<<deviceName<<size;
        if (success)
        {
            m_decoder.setDeviceSocket(m_server.getDeviceSocket());
            m_decoder.startDecode();
        }
    });

    m_frames.init();
    m_decoder.setFrames(&m_frames);
    connect(&m_decoder, &Decoder::onNewFrame, this,[this](){
        qDebug()<<"Decoder::onNewFrame";
        m_frames.lock();
        const AVFrame *frame = m_frames.consumeRenderedFrame();
        //渲染frame
        m_frames.unLock();
    });

    m_videoWidget = new QYUVOpenGLWidget();
}

Dialog::~Dialog()
{
    m_frames.deInit();
    delete ui;
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
    m_server.start("",27183,720,8000000);
    m_videoWidget->show();
}

void Dialog::on_stopServerBtn_clicked()
{
    m_server.stop();
}
