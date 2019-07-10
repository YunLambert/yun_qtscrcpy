#include <QTimer>

#ifdef Q_OS_WIN32
#include <Windows.h>
#endif
#include "videoform.h"
#include "ui_videoform.h"

#define VIDEO_FROM_WIDTH 420
#define VIDEO_FROM_HEIGHT 850

VideoForm::VideoForm(const QString& serial, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoForm),
    m_serial(serial)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setMouseTracking(true);
    ui->videoWidget->setMouseTracking(true);

    connect(&m_server, &server::serverStartResult, this, [this](bool success){
        qDebug() << "server start" << success;
    });
    connect(&m_server, &server::connectToResult, this, [this](bool success, const QString& deviceName, const QSize& size){
        qDebug() << "connectToResult" << success << deviceName << size;
        // update ui
        setWindowTitle(deviceName);
        updateShowSize(size);

        if (success) {
            m_decoder.setDeviceSocket(m_server.getDeviceSocket());
            m_decoder.startDecode();

            m_inputConvert.setDeviceSocket(m_server.getDeviceSocket());
        }
    });    

    m_frames.init();

    m_decoder.setFrames(&m_frames);

    connect(&m_server, &server::onServerStop, this, [this](){
        close();
        qDebug() << "server process stop";
    });

    connect(&m_decoder, &Decoder::onDecodeStop, this, [this](){
        close();
        qDebug() << "decoder thread stop";
    });

    connect(&m_decoder, &Decoder::onNewFrame, this, [this](){
        m_frames.lock();
        const AVFrame *frame = m_frames.consumeRenderedFrame();

        updateShowSize(QSize(frame->width, frame->height));

        // 渲染frame
        ui->videoWidget->setFrameSize(QSize(frame->width, frame->height));
        ui->videoWidget->updateTextures(frame->data[0], frame->data[1], frame->data[2], frame->linesize[0], frame->linesize[1], frame->linesize[2]);
        m_frames.unLock();
    });
    updateShowSize(size());

    // mac上adb进程无法退出
    //m_server.start(m_serial, 27183, 720, 8000000);

    QTimer::singleShot(0, this, [this](){
        m_server.start(m_serial, 27183, 720, 8000000);
    });
}

VideoForm::~VideoForm()
{
    m_server.stop();
    m_decoder.stopDecode();
    m_frames.deInit();

    delete ui;
}

void VideoForm::mousePressEvent(QMouseEvent *event)
{
    m_inputConvert.mouseEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::mouseReleaseEvent(QMouseEvent *event)
{
    m_inputConvert.mouseEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::mouseMoveEvent(QMouseEvent *event)
{
    m_inputConvert.mouseEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::wheelEvent(QWheelEvent *event)
{
    m_inputConvert.wheelEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::keyPressEvent(QKeyEvent *event)
{
    m_inputConvert.keyEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::keyReleaseEvent(QKeyEvent *event)
{
    m_inputConvert.keyEvent(event, ui->videoWidget->frameSize(), ui->videoWidget->size());
}

void VideoForm::updateShowSize(const QSize &newSize)
{
    if (m_frameSize != newSize) {
        m_frameSize = newSize;

        bool vertical = newSize.height() > newSize.width();
        if (vertical) {
            resize(VIDEO_FROM_WIDTH, VIDEO_FROM_HEIGHT);
        } else {
            resize(VIDEO_FROM_HEIGHT, VIDEO_FROM_WIDTH);
        }
    }
}
