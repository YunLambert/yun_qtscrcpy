#ifndef INPUTCONVERTBASE_H
#define INPUTCONVERTBASE_H
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include "controller.h"

class InputConvertBase
{
public:
    InputConvertBase();
    virtual ~InputConvertBase();

    virtual void mouseEvent(const QMouseEvent* from, const QSize& frameSize, const QSize& showSize) = 0;
    virtual void wheelEvent(const QWheelEvent* from, const QSize& frameSize, const QSize& showSize) = 0;
    virtual void keyEvent(const QKeyEvent* from, const QSize& frameSize, const QSize& showSize) = 0;

    void setDeviceSocket(DeviceSocket *deviceSocket);
protected:
    void sendControlEvent(ControlEvent* event);

private:
    Controller m_controller;
};
#endif // INPUTCONVERTBASE_H
