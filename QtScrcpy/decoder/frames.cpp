#include "frames.h"
extern "C"
{
#include "libavutil/avutil.h"
#include "libavformat/avformat.h"
}

Frames::Frames()
{

}

Frames::~Frames()
{

}

bool Frames::init()
{
    m_decodingFrame = av_frame_alloc();
    if (!m_decodingFrame) {
        goto error;
    }

    m_renderingframe = av_frame_alloc();
    if (!m_renderingframe) {
        goto error;
    }

    m_renderingFrameConsumed = true;
    return true;

error:
    deInit();
    return false;
}

void Frames::deInit()
{
    if (m_decodingFrame) {
        av_frame_free(&m_decodingFrame);
        m_decodingFrame = Q_NULLPTR;
    }
    if (m_renderingframe) {
        av_frame_free(&m_renderingframe);
        m_renderingframe = Q_NULLPTR;
    }
}

void Frames::lock()
{
    m_mutex.lock();
}

void Frames::unLock()
{
    m_mutex.unlock();
}

AVFrame *Frames::decodingFrame()
{
    return m_decodingFrame;
}

bool Frames::offerDecodedFrame()
{
    m_mutex.lock();
    swap();
    bool previousFrameConsumed = m_renderingFrameConsumed;
    m_renderingFrameConsumed = false;
    m_mutex.unlock();
    return previousFrameConsumed;
}

const AVFrame *Frames::consumeRenderedFrame()
{
    Q_ASSERT(!m_renderingFrameConsumed);
    m_renderingFrameConsumed = true;

    return m_renderingframe;
}

void Frames::stop()
{
}

void Frames::swap()
{
    AVFrame *tmp = m_decodingFrame;
    m_decodingFrame = m_renderingframe;
    m_renderingframe = tmp;
}
