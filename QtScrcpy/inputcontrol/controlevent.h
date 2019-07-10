#ifndef CONTROLEVENT_H
#define CONTROLEVENT_H
#include "keycodes.h"
#include "input.h"
#include "qscrcpyevent.h"
#include <QRect>
#include <QBuffer>

class ControlEvent : public QScrcpyEvent
{
public:
    enum ControlEventType {
        CET_KEYCODE = 0,
        CET_TEXT,
        CET_MOUSE,
        CET_SCROLL,
        CET_COMMAND,
        CET_TOUCH,
    };

    ControlEvent(ControlEventType type);
    void setMouseEventData(AndroidMotioneventAction action,AndroidMotioneventButtons buttons,QRect position);
    QByteArray serializeData(); //序列化数据
protected:
    void write32(QBuffer &buffer, quint32 value);
    void write16(QBuffer &buffer, quint32 value);
    void writePosition(QBuffer &buffer, QRect value);

private:
    struct ControlEventData {
        ControlEventType type;
        union {
            struct {
                AndroidMotioneventAction action;
                AndroidMotioneventButtons buttons;
                QRect position;
            }mouseEvent;
        };
        ControlEventData(){};
        ~ControlEventData(){};

    };

    ControlEventData m_data;
};

#endif // CONTROLEVENT_H
