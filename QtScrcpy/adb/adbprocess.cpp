#include <QDebug>
#include <QFileInfo>
#include <QCoreApplication>
#include "adbprocess.h"

QString AdbProcess::s_adbPath="";
AdbProcess::AdbProcess(QObject *parent)
    :QProcess(parent)
{
    initSignals();
    getAdbPath();
}

QString AdbProcess::getAdbPath()
{
    if(s_adbPath.isEmpty()){
        s_adbPath=QString::fromLocal8Bit(qgetenv("QTSCRCPY_ADB_PATH"));
        QFileInfo fileInfo(s_adbPath);
        if(s_adbPath.isEmpty() || !fileInfo.isFile()){
            s_adbPath=QCoreApplication::applicationDirPath()+"/adb";
        }
    }
    return s_adbPath;
}

void AdbProcess::execute(const QString &serial, const QStringList &args)
{
    QStringList adbArgs;
    if(!serial.isEmpty()){
        adbArgs<<"-s"<<serial;
    }
    adbArgs<<args;
    qDebug()<<getAdbPath()<<adbArgs.join(" ");
    start(getAdbPath(),adbArgs);
}

void AdbProcess::initSignals()
{
    connect(this,&QProcess::errorOccurred,this,[this](QProcess::ProcessError error){
        qDebug()<<error;
    });

    connect(this, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
         this,[this](int exitCode, QProcess::ExitStatus exitStatus){
        qDebug()<<exitCode<<exitStatus;
    });

    connect(this,&QProcess::readyReadStandardError,this,[this](){
        qDebug()<<readAllStandardError();
    });
    connect(this,&QProcess::readyReadStandardOutput,this,[this](){
        qDebug()<<readAllStandardOutput();
    });
    connect(this,&QProcess::started,this,[this](){
        qDebug()<<"started";
    });
}
