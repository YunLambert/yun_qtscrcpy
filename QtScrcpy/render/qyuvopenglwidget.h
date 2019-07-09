#ifndef QYUVOPENGLWIDGET_H
#define QYUVOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

class QYUVOpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit QYUVOpenGLWidget(QWidget *parent = nullptr);
    virtual ~QYUVOpenGLWidget();

    // QWidget虚函数
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    // 设置视频帧尺寸，用于生成纹理
    void setFrameSize(const QSize& frameSize);
    // 返回当前视频帧尺寸
    const QSize& frameSize();
    // 渲染视频帧
    void updateTextures(quint8* dataY, quint8* dataU, quint8* dataV, quint32 linesizeY, quint32 linesizeU, quint32 linesizeV);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

private:    
    // 初始化着色器
    void initShader();
    // 初始化纹理
    void initTextures();
    // 清理纹理
    void deInitTextures();
    // 更新纹理
    void updateTexture(GLuint texture, quint32 textureType, quint8* pixels, quint32 stride);

private:
    // 视频帧尺寸
    QSize m_frameSize = {-1, -1};
    // 是否更新标志
    bool m_needUpdate = false;
    // 纹理初始化标志
    bool m_textureInited = false;

    // 顶点缓冲对象(Vertex Buffer Objects, VBO)：默认即为VertexBuffer(GL_ARRAY_BUFFER)类型
    QOpenGLBuffer m_vbo;

    // 着色器程序：编译链接着色器
    QOpenGLShaderProgram m_shaderProgram;    

    // YUV纹理，用于生成纹理贴图
    GLuint m_texture[3] = {0};
};

#endif // QYUVOPENGLWIDGET_H
