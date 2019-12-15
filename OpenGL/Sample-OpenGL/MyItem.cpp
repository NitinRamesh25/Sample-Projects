#include "MyItem.h"

MyItem::MyItem(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
    , m_renderer(createRenderer())
{}

QQuickFramebufferObject::Renderer *MyItem::renderer() const
{
    return m_renderer;
}

QQuickFramebufferObject::Renderer *MyItem::createRenderer() const
{
    return new MyItemRenderer;
}


MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();

     glClearColor(0.1f, 0.1f, 0.2f, 0.0f); // transparent

     // just the default shaders:
     const char *vertexShaderSrc =
         "attribute highp vec4 posAttr;\n"
         "attribute lowp vec4 colAttr;\n"
         "varying lowp vec4 col;\n"
         "uniform highp mat4 matrix;\n"
         "void main() {\n"
         "   col = colAttr;\n"
         "   gl_Position = matrix * posAttr;\n"
         "}\n";

     const char *fragmentShaderSrc =
         "varying lowp vec4 col;\n"
         "void main() {\n"
         "   gl_FragColor = col;\n"
         "}\n";

     shader_->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSrc);
     shader_->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSrc);
     shader_->link();
     positionAttr_ = shader_->attributeLocation("posAttr");
     colorAttr_ = shader_->attributeLocation("colAttr");
     matrixAttr_ = shader_->uniformLocation("matrix");
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    window_ = item->window();

    auto* myItem = static_cast<MyItem*>(item);
    Q_UNUSED(myItem)

    // fetch required properties from myItem and store as member variables in renderer.
}

void MyItemRenderer::render()
{
    // use OpenGl 2.0
    glClear(GL_COLOR_BUFFER_BIT);

    shader_->bind();

    QMatrix4x4 matrix;
    matrix.perspective(90.0f, 1.0f, 0.1f, 100.0f);
    matrix.translate(0, 0, -1);

    shader_->setUniformValue(matrixAttr_, matrix);

    float relSize = 0.8f;
    GLfloat vertices[] = {
        -relSize, -relSize, 0.0f,
        relSize, -relSize, 0.0f,
        0.0f, relSize, 0.0f
    };

    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    glVertexAttribPointer(positionAttr_, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(colorAttr_, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    shader_->release();
}

QOpenGLFramebufferObject* MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}


