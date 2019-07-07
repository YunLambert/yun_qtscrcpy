#include "qyuvopenglwidget.h"

QYUVOpenGLWidget::QYUVOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

void QYUVOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //设置背景
    glClearColor(255, 0, 0, 0); //red green blue alpha
}

void QYUVOpenGLWidget::resizeGL(int w, int h)
{

}

void QYUVOpenGLWidget::paintGL()
{

}
