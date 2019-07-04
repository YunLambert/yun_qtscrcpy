#ifndef SERVER_H
#define SERVER_H
#include <QObject>
#include <QTcpSocket
#include "adbprocess.h"

class server:public QObject
{
    Q_OBJECT

    enum SERVER_START_STEP {
        SSS_NULL, //空闲状态
        SSS_PUSH, //push到安卓手机上
        SSS_ENABLE_REVERSE, //启动反向代理
        SSS_EXECUTE_SERVER, //启动服务器
        SSS_RUNNING, //运行服务器
    };

public:
    server(QObject *parent = Q_NULLPTR);
    bool start(const QString& serial,quint16 localPort, quint16 maxSize, quint32 bitRate);

signals:
    void serverStartResult(bool success);

private slots:
    void onWorkProcessResult(AdbProcess::ADB_EXEC_RESULT processResult);

private:
    bool startServerByStep();
    bool pushServer();
    bool removeServer();
    bool enableTunnelReverse();
    bool disableTunnelReverse();
    bool execute();
    QString getServerPath();

private:
    QString m_serial = "";
    quint16 m_localPort=0;
    quint16 m_maxSize = 0;
    quint32 m_bitRate = 0;

    SERVER_START_STEP m_serverStartStep = SSS_NULL; //初始化服务器的起始状态

    AdbProcess m_workProcess;
    AdbProcess m_serverProcess;
    QString m_serverPath = "";
    bool m_serverCopiedToDevice = false; //是否成功将server.jar push到了安卓设备上
    bool m_enableReverse = false;

    QTcpServer m_serverSocket;
    QTcpSocket* m_deviceSocket = Q_NULLPTR;
};

#endif // SERVER_H
