#include "MyItemRenderer.h"

MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    m_size = item->size();
}

void MyItemRenderer::render()
{
    glViewport(0, 0, m_size.width(), m_size.height());

    // Clear the view port of previous colors and set new color.
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    // Have to inform that color bits have been cleared otherwise the new color
    // wont fill the view port.
    // Other options are GL_DEPTH_BUFFER_BIT and GL_STENCIL_BUFFER_BIT
    glClear(GL_COLOR_BUFFER_BIT);
}

QOpenGLFramebufferObject* MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}
