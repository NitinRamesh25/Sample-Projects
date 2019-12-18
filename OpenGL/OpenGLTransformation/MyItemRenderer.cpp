#include "MyItemRenderer.h"
#include "MyItem.h"

MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();
    createShader();
    createBuffer();
}

QOpenGLFramebufferObject* MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    auto* myItem = dynamic_cast<MyItem*>(item);
    if(nullptr != myItem)
    {
        m_window = myItem->window();
        m_size = myItem->size();
    }
}

void MyItemRenderer::render()
{

}

void MyItemRenderer::createShader()
{
    const char* vertexShaderSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0f);\n"
        "}\0";
}

void MyItemRenderer::createBuffer()
{

}
