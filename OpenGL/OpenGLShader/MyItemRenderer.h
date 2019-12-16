#pragma once

#include <QQuickWindow>
#include <QQuickFramebufferObject>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_3_0>

#include <QColor>

class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions_3_0
{
public:
    MyItemRenderer();

protected:

    void createGeometry();
    void createShaderProgram();

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;
    void synchronize(QQuickFramebufferObject *item) override;
    void render() override;

    bool verifyShaderProgramCompilation(GLuint programId);
    bool verifyShaderObjectCompilation(GLuint shaderId, GLuint shaderType);

private:
    QQuickWindow* m_window;
    QSizeF m_size;

    GLuint m_vao;
    GLuint m_vbo;
    GLint m_shaderProgram;
};

