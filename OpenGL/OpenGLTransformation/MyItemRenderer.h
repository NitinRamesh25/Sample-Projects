#pragma once

#include <QQuickWindow>
#include <QQuickFramebufferObject>

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFramebufferObject>

#include <QMatrix4x4>
#include <QVector3D>

class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions_3_0
{
public:
    MyItemRenderer();

    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) override;
    void synchronize(QQuickFramebufferObject *item) override;
    void render() override;

protected:
    void createShader();
    void createBuffer();

    bool verifyShaderCompilation(GLuint shader, QString shaderName);
    bool verifyProgramLink(GLuint program);

    void applyTransform();

    QQuickWindow* m_window;
    QSizeF m_size;

    GLuint m_shaderProgram;
    GLint m_colorLocation;
    GLint m_transformLocation;

    GLuint m_vao;
};

