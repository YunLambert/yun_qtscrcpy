#ifndef DECODER_H
#define DECODER_H

#include <QThread>
#include <QPointer>
#include <QMutex>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}

class Frames;
class DeviceSocket;
class Decoder : public QThread
{
    Q_OBJECT
public:
    Decoder();
    virtual ~Decoder();

public:
    static bool init();
    static void deInit();    

    void setFrames(Frames* frames);
    void setDeviceSocket(DeviceSocket* deviceSocket);
    qint32 recvData(quint8* buf, qint32 bufSize);
    bool startDecode();
    void stopDecode();

signals:
    void onNewFrame();
    void onDecodeStop();

protected:
    void run();
    void pushFrame();

private:
    // 接收h264数据
    QPointer<DeviceSocket> m_deviceSocket;    
    // 退出标记
    bool m_quit = false;
    // 解码出的帧
    Frames* m_frames;
};

#endif // DECODER_H
