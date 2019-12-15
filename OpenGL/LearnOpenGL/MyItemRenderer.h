#pragma once

#include <QQuickFramebufferObject>

#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>

#include "MyItem.h"

class MyItemRenderer
    : public QQuickFramebufferObject::Renderer
    , protected QOpenGLFunctions
{
public:
    MyItemRenderer();

protected:
    void synchronize(QQuickFramebufferObject *item) override;

    void render() override;

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    QSizeF m_size;
};

