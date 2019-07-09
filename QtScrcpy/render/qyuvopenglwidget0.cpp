#include "qyuvopenglwidget.h"
#include <QDebug>

// 定义三角形定点数组,OpenGl仅在-1，1之间进行处理
float vertices[]={
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};

//顶点着色器源码
const char* vertexShaderSource = "layout (location = 0) in vec3 aPos; \
        void main() \
        { \
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
        }";

//片段着色器源码
const char* fragmentShaderSource = "out vec4 FragColor; \
        void main() \
        { \
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\
        } ";


QYUVOpenGLWidget::QYUVOpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{

}

void QYUVOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //设置背景
    glClearColor(255, 0, 0, 0); //red green blue alpha

    // 顶点缓冲对象，可以一次性发送一大批数据到显卡
    unsigned int VBO;    //定义顶点缓冲对象id
    glGenBuffers(1, &VBO); //生成顶点缓冲对象
    glBindBuffer(GL_ARRAY_BUFFER,VBO); //绑定顶点缓冲对象到opengl，告诉opengl顶点数组缓存使用我们的顶点缓冲对象
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 顶点着色器：控制绘制图形的位置
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // 指定顶点着色器源码
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // 编译着色器
    glCompileShader(vertexShader);

    // 片段着色器，控制绘制图形的颜色
    unsigned int fragmentShader; // 定义片段着色器id
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // 创建片段着色器:GL_FRAGMENT_SHADER片段着色器
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //指定片段着色器
    glCompileShader(fragmentShader); //编译片段着色器

    //着色器程序:链接着色器，将着色器应用到opengl中
    unsigned int shaderProgram;        //定义着色器程序id
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    qDebug()<<"drawing....";
}

void QYUVOpenGLWidget::resizeGL(int w, int h)
{

}

void QYUVOpenGLWidget::paintGL()
{
    qDebug()<<"Drawing Triangles!";
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
