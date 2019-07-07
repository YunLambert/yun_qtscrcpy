#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "server.h"
#include "adbprocess.h"
#include "decoder.h"
#include "frames.h"
#include "qyuvopenglwidget.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_startServerBtn_clicked();

    void on_stopServerBtn_clicked();

private:
    Ui::Dialog *ui;

    server m_server;
    Decoder m_decoder;
    Frames m_frames;
    QYUVOpenGLWidget* m_videoWidget;
};

#endif // DIALOG_H
