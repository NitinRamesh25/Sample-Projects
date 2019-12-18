#pragma once

#include <QQuickWindow>
#include <QQuickFramebufferObject>

#include <QOpenGLFunctions_3_0>
#include <QOpenGLFramebufferObject>

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

    QQuickWindow* m_window;
    QSizeF m_size;
};

