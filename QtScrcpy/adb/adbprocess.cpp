#include "adbprocess.h"
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QFileInfo>

QString AdbProcess::s_adbPath = "";

AdbProcess::AdbProcess(QObject *parent)
    : QProcess(parent)
{
    initSignals();
    getAdbPath();
}

QString AdbProcess::getAdbPath()
{
    if (s_adbPath.isEmpty()) {
        s_adbPath = QString::fromLocal8Bit(qgetenv("QTSCRCPY_ADB_PATH"));
        QFileInfo fileInfo(s_adbPath);
        if (s_adbPath.isEmpty() || !fileInfo.isFile()) {
            s_adbPath = QCoreApplication::applicationDirPath() + "/adb";
        }
    }
    return s_adbPath;
}

void AdbProcess::initSignals()
{
    connect(this, &QProcess::errorOccurred, this, [this](QProcess::ProcessError error){
        if (QProcess::FailedToStart == error) {
            emit adbProcessResult(AER_ERROR_MISSING_BINARY);
        }
        else
        {
            emit adbProcessResult(AER_ERROR_START);
        }
        qDebug()<<error;
    });

    connect(this, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this, [this](int exitCode, QProcess::ExitStatus exitStatus){
        if (QProcess::NormalExit == exitStatus && exitCode == 0)
            emit adbProcessResult(AER_SUCCESS_EXEC);
        else
            emit adbProcessResult(AER_ERROR_EXEC);
        qDebug()<<exitCode<<exitStatus;
    });

    connect(this, &QProcess::readyReadStandardError, this, [this](){
        qDebug()<<readAllStandardError();

    });

    connect(this, &QProcess::readyReadStandardOutput,this,[this](){
        qDebug()<<readAllStandardOutput();
    });

    connect(this,&QProcess::started,this,[this](){
        emit adbProcessResult(AER_SUCCESS_START);
    });
}

void AdbProcess::execute(const QString &serial, const QStringList &args)
{
    QStringList adbArgs;
    if (!serial.isEmpty()) {
        adbArgs<<"-s"<<serial;
    }
    adbArgs<<args;
    qDebug()<<getAdbPath()<<adbArgs.join(" ");
    start(getAdbPath(), adbArgs);

}
