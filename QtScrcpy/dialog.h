#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPointer>
#include "server.h"
#include "adbprocess.h"
#include "decoder.h"
#include "frames.h"
#include "qyuvopenglwidget.h"
#include "controller.h"
#include "videoform.h"

namespace Ui {
class Dialog;
}

class VideoForm;
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_startServerBtn_clicked();

    void on_stopServerBtn_clicked();

    void on_touchButton_clicked();

private:
    Ui::Dialog *ui;

    QPointer<VideoForm> m_videoForm;

};

#endif // DIALOG_H
