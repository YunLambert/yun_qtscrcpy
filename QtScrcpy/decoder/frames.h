#ifndef FRAMES_H
#define FRAMES_H

#include <QMutex>
#include <QWaitCondition>

// forward declarations
typedef struct AVFrame AVFrame;

class Frames
{
public:
    Frames();
    virtual ~Frames();

    bool init();
    void deInit();
    void lock();
    void unLock();

    AVFrame* decodingFrame();
    bool offerDecodedFrame();
    const AVFrame* consumeRenderedFrame();
    void stop();

private:
    void swap();

private:
    // 解码出来的一帧数据（yuv）
    // 保存正在解码的yuv
    AVFrame* m_decodingFrame = Q_NULLPTR;
    // 保存正在渲染的yuv
    AVFrame* m_renderingframe = Q_NULLPTR;
    // 保证AVFrame的多线程安全
    QMutex m_mutex;
    bool m_renderingFrameConsumed = true;
};

#endif // FRAMES_H
