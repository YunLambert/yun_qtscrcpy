#ifndef INPUTCONVERTNORMAL_H
#define INPUTCONVERTNORMAL_H
#include "controlevent.h"
#include "inputconvertbase.h"

class InputConvertNormal : public InputConvertBase
{
public:
    InputConvertNormal();
    virtual ~InputConvertNormal();

    virtual void mouseEvent(const QMouseEvent* from, const QSize& frameSize, const QSize& showSize);
    virtual void wheelEvent(const QWheelEvent* from, const QSize& frameSize, const QSize& showSize);
    virtual void keyEvent(const QKeyEvent* from, const QSize& frameSize, const QSize& showSize);

private:
    AndroidMotioneventButtons convertMouseButtons(Qt::MouseButtons buttonState);
    AndroidKeycode convertKeyCode(int key, Qt::KeyboardModifiers modifiers);
    AndroidMetastate convertMetastate(Qt::KeyboardModifiers modifiers);

};

#endif // INPUTCONVERTNORMAL_H
