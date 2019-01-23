#include <QFileInfo>
#include <QCoreApplication>
#include "server.h"

#define DEVICE_SERVER_PATH "/data/local/tmp/scrcpy-server.jar"
#define SOCKET_NAME "scrcpy"
server::server(QObject *parent)
    :QObject(parent)
{
    connect(&m_workProcess,&AdbProcess::adbProcessResult,this,&server::onWorkProcessResult);
    connect(&m_serverProcess,&AdbProcess::adbProcessResult,this,&server::onWorkProcessResult);
}

bool server::start(const QString &serial, quint16 localPort, quint16 maxSize, quint32 bitRate)
{
    m_serial=serial;
    m_localPort=localPort;
    m_maxSize=maxSize;
    m_bitRate=bitRate;

    //start oush server
    m_serverStartStep=SSS_PUSH;
    return startServerByStep();
}

void server::onWorkProcessResult(AdbProcess::ADB_EXEC_RESULT processResult)
{
    if(sender()==&m_workprocess)
    {
        if(m_serverStartStep!=SSS_NULL)
        {
            switch(m_serverStartStep)
            {
            case SSS_PUSH:
                if(processResult==AdbProcess::AER_SUCCESS_EXEC)
                {
                    m_serverCopiedToDevice=true;
                    m_serverStartStep=SSS_ENABLE_REVERSE;
                    startServerByStep();
                }
                else if(processResult!=AdbProcess::AER_SUCCESS_START)
                {
                    qCritical("adb push failed");
                    m_serverStartStep=SSS_NULL;
                    emit serverStartResult(false);
                }
                break;
             case SSS_ENABLE_REVERSE:
                if(processResult==AdbProcess::AER_SUCCESS_EXEC)
                {
                    m_enableReverse=true;
                    m_serverStartStep=SSS_EXECUTE_SERVER;
                    startServerByStep();
                }
                else if(processResult!=AdbProcess::AER_SUCCESS_START)
                {
                    qCritical("adb reverse failed");
                    m_serverStartStep=SSS_NULL;
                    removeServer();
                    emit serverStartResult(false);
                }
                break;
             default:
                break;
            }
        }
    }
    if(sender()==&m_serverProcess){
        if(m_serverStartStep==SSS_EXECUTE_SERVER){
            if(processResult==AdbProcess::AER_SUCCESS_START){
                m_serverStartStep=SSS_RUNNING;
                emit serverStartResult(true);
            }
            else if(processResult==AdbProcess::AER_ERROR_START)
            {
                //disable reverse
                disableTunnelReverse();
                qCritical("adb shell start server failed");
                m_serverStartStep=SSS_NULL;
                //remove server
                removeServer();
                emit serverStartResult(false);
            }
        }
    }

}

bool server::startServerByStep()
{
    bool stepSuccess=false;
    //push,enable reverse,execute server
    if(m_serverStartStep!=SSS_NULL)
    {
        switch(m_serverStartStep)
        {
            case SSS_PUSH:
                stepSuccess=pushServer();
                break;
            case SSS_ENABLE_REVERSE:
                stepSuccess=enableTunnelReverse();
                break;
            case SSS_EXECUTE_SERVER:
                stepSuccess=execute();
                break;
            default:
                break;
        }
    }
    return stepSuccess;
}

bool server::pushServer()
{
    m_workProcess.push(m_serial,getServerPath(),DEVICE_SERVER_PATH);
    return true;
}

bool server::removeServer()
{
    if(!m_serverCopiedToDevice){
        return true;
    }
    m_serverCopiedToDevice=false;
    //m_workProcess.remotePath(m_serial,DEVICE_SERVER_PATH)
    AdbProcess* adb=new AdbProcess();   //并不关心这个的结果，这是为了清理掉，所以新建了adb
    if(!adb)
    {
        return false;
    }
    connect(adb,&AdbProcess::adbProcessResult,this,[this](AdbProcess::ADB_EXEC_RESULT processResult){
        if(processResult!=AdbProcess::AER_SUCCESS_START)
        {
            sender()->deleteLater();  //槽函数，可以获得发出信号的对象，自动释放掉adb
        }
    });
    adb->removePath(m_serial,DEVICE_SERVER_PATH);
    return true;
}

bool server::enableTunnelReverse()
{
    m_workProcess.reverse(m_serial,SOCKET_NAME,m_localPort);
    return true;
}

bool server::disableTunnelReverse()
{
    if(!m_enableReverse)
    {
        return true;
    }
    m_enableReverse=false;
    AdbProcess* adb=new AdbProcess();   //并不关心这个的结果，这是为了清理掉，所以新建了adb
    if(!adb)
    {
        return false;
    }
    connect(adb,&AdbProcess::adbProcessResult,this,[this](AdbProcess::ADB_EXEC_RESULT processResult){
        if(processResult!=AdbProcess::AER_SUCCESS_START)
        {
            sender()->deleteLater();  //槽函数，可以获得发出信号的对象，自动释放掉adb
        }
    });
    adb->reverseRemove(m_serial,SOCKET_NAME);
    return true;
}

bool server::execute()
{
    QStringList args;
    args<<"shell";
    args<<QString("CLASSPATH=%1").arg(DEVICE_SERVER_PATH);
    args<<"/";
    args<<"com.genymobile.scrcpy.Server";
    args<<QString::number(m_maxSize);
    args<<QString::number(m_bitRate);
    args<<false;
    args<<"";
    m_serverProcess.execute(m_serial,args);
    return true;
}

QString server::getServerPath()
{
    if(m_serverPath.isEmpty()){
        m_serverPath=QString::fromLocal8Bit(qgetenv("QTSCRCPY_SERVER_PATH"));
        QFileInfo fileInfo(m_serverPath);
        if(m_serverPath.isEmpty() || !fileInfo.isFile()){
            m_serverPath=QCoreApplication::applicationDirPath()+"/scrcpy-server.jar";
        }
    }
    return m_serverPath;
}
