#ifndef DEVICESOCKET_H
#define DEVICESOCKET_H

#include <QTcpSocket>
#include <QWaitCondition>  //条件变量用来通知消费者数据到来
#include <QMutex>         //用来保证条件变量的正确性

class DeviceSocket : public QTcpSocket
{
    Q_OBJECT
public:
    DeviceSocket(QObject *parent = Q_NULLPTR);
    ~DeviceSocket();

    //封装一个接口，供解码器使用->子线程调用，获取H264数据
    qint32 subThreadRecvData(quint8* buf, qint32 bufSize);

protected:
    bool event(QEvent *event);

protected slots:
    void onReadyRead();
    void quitNotify();

private:
    //锁
    QMutex m_mutex;
    QWaitCondition m_recvDataCond;

    //标志
    bool m_recvData = false;
    bool m_quit = false;

    //数据缓存
    quint8* m_buffer = Q_NULLPTR;
    qint32 m_bufferSize = 0; //缓冲区大小
    qint32 m_dataSize = 0;   //实际收到数据，可能小于bufferSize的
};

#endif // DEVICESOCKET_H
