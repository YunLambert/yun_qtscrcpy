#ifndef DEVICESOCKET_H
#define DEVICESOCKET_H

#include <QTcpSocket>
#include <QwaitCondition>   //条件变量，用来通知消费者消息到来
#include <QMutex>    //互斥锁，保证安全性

class DeviceSocket:public QTcpSocket
{
    Q_OBJECT
public:
    DeviceSocket(QObject *parent=Q_NULLPTR);
    ~DeviceSocket();

    qint32 subThreadRecvData(quint8* buf,qint32 bufSize);

protected:
    bool event(QEvent *event);

private slots:
    void onReadyRead();
    void quitNotify();

private:
    QMutex m_mutex;
    QWaitCondition m_recvDataCond;  //通过条件变量通知解码线程

    // 标志
    bool m_recvData=false;
    bool m_quit=false;

    // 数据缓存
    quint8* m_buffer=Q_NULLPTR;
    qint32 m_bufferSize=0;
    qint32 m_dataSize=0;

};

#endif // DEVICESOCKET_H
