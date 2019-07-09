#ifndef QYUVOPENGLWIDGET_H
#define QYUVOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class QYUVOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    QYUVOpenGLWidget(QWidget* parent=Q_NULLPTR);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w,int h);
    virtual void paintGL();
};

#endif // QYUVOPENGLWIDGET_H
