#ifndef VIDEOFORM_H
#define VIDEOFORM_H

#include <QWidget>

#include "server.h"
#include "decoder.h"
#include "frames.h"
#include "qyuvopenglwidget.h"
#include "inputconvertnormal.h"
#include "inputconvertgame.h"


namespace Ui {
class VideoForm;
}

class VideoForm : public QWidget
{
    Q_OBJECT

public:
    explicit VideoForm(const QString& serial, QWidget *parent = 0);
    ~VideoForm();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

//    virtual void wheelEvent(QWheelEvent *event);

//    virtual void keyPressEvent(QKeyEvent *event);
//    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    void updateShowSize(const QSize &newSize);

private:
    Ui::VideoForm *ui;
    QString m_serial = "";

    server m_server;
    Decoder m_decoder;
    Frames m_frames;
    InputConvertNormal m_inputConvert;
//    InputConvertGame m_inputConvert;

    QSize m_frameSize;
};

#endif // VIDEOFORM_H
