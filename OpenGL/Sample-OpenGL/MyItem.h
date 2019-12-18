#pragma once

#include <QQuickFramebufferObject>
#include <QQuickWindow>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions_3_0>
#include <QOpenGLShaderProgram>


class MyItem : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    MyItem(QQuickItem* parent = nullptr);

protected:
    Renderer * createRenderer() const override;

};


class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions_3_0
{

public:
    MyItemRenderer();

    void synchronize(QQuickFramebufferObject *item) override;

    void render() override;

    QOpenGLFramebufferObject * createFramebufferObject(const QSize &size) override;

private:
    QQuickWindow* m_window;
    QSizeF m_size;

    GLuint m_shaderProgram;
    GLint m_colorLocation;

    GLuint m_vao;
};

