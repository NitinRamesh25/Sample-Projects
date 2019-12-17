#pragma once
#include <QQuickFramebufferObject>
#include <QQuickWindow>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_3_0>


class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions_3_0
{
public:
    MyItemRenderer();
    virtual ~MyItemRenderer();

    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) override;
    void synchronize(QQuickFramebufferObject* item) override;
    void render() override;

protected:
    void initBufferMemory();
    void initTexture();
    void initShaderProgram();

    void verifyShaderCompilation(GLuint shader, const QString& shaderType);
    void verifyShaderProgramCompilation(GLuint program);

    QQuickWindow* m_window;
    QSizeF m_size;

    // Vertex Array Object
    GLuint m_vao;
    // Vertex Buffer Object
    GLuint m_vbo;
    // Element Buffer Object
    GLuint m_ebo;

    GLuint m_shaderProgram;
    GLuint m_texture;
};

