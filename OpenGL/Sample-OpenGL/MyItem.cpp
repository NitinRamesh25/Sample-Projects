#include "MyItem.h"
#include <QThread>

MyItem::MyItem(QQuickItem* parent)
    : QQuickFramebufferObject(parent)
{}

QQuickFramebufferObject::Renderer *MyItem::createRenderer() const
{
    return new MyItemRenderer;
}


MyItemRenderer::MyItemRenderer()
{
    initializeOpenGLFunctions();

    // just the default shaders:
    const char *vertexShaderSrc =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "gl_Position = vec4(aPos, 1.0f);\n"
        "}\0";

    const char *fragmentShaderSrc =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "uniform vec4 myColor;\n"
        "void main()\n"
        "{\n"
        "fragColor = myColor;\n"
        "}\0";

    auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    m_colorLocation = glGetUniformLocation(m_shaderProgram, "myColor");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    GLuint vbo;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void MyItemRenderer::synchronize(QQuickFramebufferObject *item)
{
    auto* myItem = static_cast<MyItem*>(item);
    m_window = myItem->window();
    m_size = myItem->size();
}

void MyItemRenderer::render()
{
    glViewport(0, 0, 2 * m_size.width(), 2 * m_size.height());

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_shaderProgram);
    glBindVertexArray(m_vao);

    glUniform4f(m_colorLocation, 1.0f, 0.0f, 0.0f, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    m_window->resetOpenGLState();

}

QOpenGLFramebufferObject* MyItemRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setSamples(4);
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}


